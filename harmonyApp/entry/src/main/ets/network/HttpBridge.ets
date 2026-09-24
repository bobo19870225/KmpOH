import { rcp } from '@kit.RemoteCommunicationKit';
import { util } from '@kit.ArkTS';
import { hilog } from '@kit.PerformanceAnalysisKit';
import nativeApi from 'libentry.so';
import { SuppressWarnings, SuppressWarningsType } from '@kit.BasicServicesKit';

/**
 * KMP HTTP 传输桥（ArkTS 侧）——经 RCP（RemoteCommunicationKit）执行实际网络请求，
 * 系统 TLS 栈完成 HTTPS 握手。
 *
 * 方案对齐 Technician-Harmony 的 network/RcpSession.ets + HttpClient.ets（RCP + TlsV1.3
 * + 超时配置）；差异：本文件是**纯传输层**，信封解析/签名/鉴权/日志均在 Kotlin 网络层
 * （ApiCall/ApiGateway/signature），此处不重复做错误拦截，任意 HTTP 状态码原样回传。
 *
 * 线协议（与 Kotlin 侧 bridge/RcpHttpClientEngine.kt + commonMain/BridgeWireBody.kt 同构，
 * **改一侧必改另一侧**）：
 * - 请求：{ url, method, headers, bodyJson?|bodyForm?|bodyMultipart?|bodyBase64? }
 *   （bodyJson 是 JSON 文本，此处 JSON.parse 成对象交 RCP——与 Technician-Harmony 传
 *   Record 同路径，RCP 按对象自动以 application/json 发出；bodyForm 为简单表单字段表，
 *   用 rcp.Form 发 application/x-www-form-urlencoded；bodyMultipart 为多部件字段表，
 *   用 rcp.MultipartForm 发 multipart/form-data；bodyBase64 为二进制原始字节。
 *   裸 string/ArrayBuffer 会被 RCP 按 text/plain/octet-stream 发出、服务端读不到参数，
 *   表单/multipart 必须走 Form/MultipartForm，禁止降级为 bodyBase64）
 * - 成功响应：{ status, headers, bodyBase64, error:'', rcpCode:0 }
 * - 传输失败：{ error, rcpCode, status:0, headers:{}, bodyBase64:'' }
 *
 * 入口 executeTransport 由 Index.ets 注册给 libentry.so 的 RegisterHttpExecutor，
 * 完成后调 nativeApi.HttpBridgeRespond(reqId, respJson) 回传。
 */

const DOMAIN = 0x0000;
const TAG = 'KmpHttpBridge';
// 对齐 Technician-Harmony utils/Constants.ets 的 CONNECT_TIMEOUT / READ_TIMEOUT
const CONNECT_TIMEOUT_MS = 10000;
const TRANSFER_TIMEOUT_MS = 30000;

/** 传输请求（Kotlin 侧 RcpHttpClientEngine.encodeRequest 的同构形态）。 */
class TransportRequest {
  url: string = '';
  method: string = 'GET';
  headers: Record<string, string> = {};
  bodyJson?: string;
  bodyForm?: Record<string, string>;
  bodyMultipart?: Record<string, string>;
  bodyBase64?: string;
}

/** 传输响应。 */
class TransportResponse {
  status: number = 0;
  headers: Record<string, string> = {};
  bodyBase64: string = '';
  error: string = '';
  rcpCode: number = 0;
}

let session: rcp.Session | null = null;

/** 获取 RCP Session（系统 TLS 1.3 + 超时；对齐 Technician-Harmony RcpSession 配置）。 */
function getSession(): rcp.Session {
  if (session === null) {
    const config: rcp.SessionConfiguration = {
      requestConfiguration: {
        security: {
          tlsOptions: {
            tlsVersion: 'TlsV1.3'
          }
        },
        transfer: {
          timeout: {
            connectMs: CONNECT_TIMEOUT_MS,
            transferMs: TRANSFER_TIMEOUT_MS
          }
        }
      }
    };
    try {
      session = rcp.createSession(config);
    } catch (error) {
      throw new Error('RCP createSession failed: ' + String(error));
    }
  }
  return session;
}

/** 把响应 JSON 回传给 Kotlin（任何异常都不得抛回 NAPI 层）。 */
function respond(requestId: string, payload: TransportResponse): void {
  try {
    nativeApi.HttpBridgeRespond(requestId, JSON.stringify(payload));
  } catch (error) {
    hilog.error(DOMAIN, TAG, 'HttpBridgeRespond failed: %{public}s', String(error));
  }
}

function fail(requestId: string, message: string, rcpCode: number): void {
  const payload = new TransportResponse();
  payload.error = message;
  payload.rcpCode = rcpCode;
  respond(requestId, payload);
}

/** 从 RCP BusinessError 提取错误码（1007900001-1007900999，语义见 Kotlin mapRcpFailure）。 */
function rcpCodeOf(error: Object): number {
  const record = error as Record<string, Object>;
  const code = record['code'];
  return typeof code === 'number' ? code : 0;
}

function flattenHeaders(headers?: rcp.ResponseHeaders): Record<string, string> {
  const result: Record<string, string> = {};
  if (headers) {
    const keys = Object.keys(headers);
    for (let i = 0; i < keys.length; i++) {
      const key = keys[i];
      const value = headers[key];
      if (typeof value === 'string') {
        result[key] = value;
      } else if (value !== undefined) {
        result[key] = value.join(', ');
      }
    }
  }
  return result;
}

function buildContent(req: TransportRequest): rcp.RequestContent | undefined {
  if (req.bodyJson !== undefined) {
    // JSON 对象交 RCP（自动 application/json）——与 Technician-Harmony 传 Record 同路径。
    // 裸 string/ArrayBuffer 会被 RCP 按 text/plain/octet-stream 发出，服务端读不到参数。
    return JSON.parse(req.bodyJson) as Object;
  }
  if (req.bodyForm !== undefined) {
    // RCP 原生简单表单：application/x-www-form-urlencoded（与原工程 @FormUrlEncoded 同形）
    const fields: rcp.FormFields = {};
    const formKeys = Object.keys(req.bodyForm);
    for (let i = 0; i < formKeys.length; i++) {
      fields[formKeys[i]] = req.bodyForm[formKeys[i]];
    }
    return new rcp.Form(fields);
  }
  if (req.bodyMultipart !== undefined) {
    // RCP 原生多部件表单：multipart/form-data（与原工程 @Multipart 同形；文件字段随上传能力扩展）
    const fields: rcp.MultipartFormFields = {};
    const partKeys = Object.keys(req.bodyMultipart);
    for (let i = 0; i < partKeys.length; i++) {
      fields[partKeys[i]] = req.bodyMultipart[partKeys[i]];
    }
    return new rcp.MultipartForm(fields);
  }
  if (req.bodyBase64 !== undefined && req.bodyBase64.length > 0) {
    const helper = new util.Base64Helper();
    return helper.decodeSync(req.bodyBase64);
  }
  return undefined;
}

/**
 * 执行传输请求（注册给 RegisterHttpExecutor 的入口）。
 * 不做同步重活：立即返回，结果经 HttpBridgeRespond 异步回传。
 */
@SuppressWarnings({ rules: [SuppressWarningsType.PERMISSION] })
export function executeTransport(requestId: string, reqJson: string): void {
  let req: TransportRequest;
  try {
    req = JSON.parse(reqJson) as TransportRequest;
  } catch (error) {
    fail(requestId, 'bridge request decode failed: ' + String(error), 0);
    return;
  }
  const content = buildContent(req);
  let request: rcp.Request;
  try {
    request = new rcp.Request(req.url, req.method, req.headers, content);
  } catch (error) {
    fail(requestId, 'bridge request build failed: ' + String(error), 0);
    return;
  }
  getSession()
    .fetch(request)
    .then((response: rcp.Response) => {
      const helper = new util.Base64Helper();
      const body: Uint8Array = response.body !== undefined
        ? new Uint8Array(response.body)
        : new Uint8Array(0);
      const payload = new TransportResponse();
      payload.status = response.statusCode;
      payload.headers = flattenHeaders(response.headers);
      payload.bodyBase64 = helper.encodeToStringSync(body);
      respond(requestId, payload);
    })
    .catch((error: Error) => {
      hilog.warn(DOMAIN, TAG, 'transport failed: %{public}s', String(error?.message));
      fail(requestId, error?.message ?? String(error), rcpCodeOf(error));
    });
}
