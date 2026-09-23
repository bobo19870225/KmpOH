package com.example.kmpoh.storage

import kotlin.test.Test
import kotlin.test.assertEquals
import kotlin.test.assertTrue

/** 内存版 KeyValueStore，供单测使用。 */
class FakeKeyValueStore : KeyValueStore {
    val data = mutableMapOf<String, String>()
    override fun getString(key: String): String? = data[key]
    override fun putString(key: String, value: String) {
        data[key] = value
    }

    override fun remove(key: String) {
        data.remove(key)
    }
}

class DeviceIdentityTest {

    @Test
    fun firstCallGeneratesAndPersistsDeviceId() {
        val store = FakeKeyValueStore()
        val id = getOrCreateDeviceId(store)
        assertTrue(id.isNotBlank())
        assertEquals(id, store.getString(StorageKeys.DEVICE_ID))
    }

    @Test
    fun subsequentCallsReturnSameId() {
        val store = FakeKeyValueStore()
        val first = getOrCreateDeviceId(store)
        val second = getOrCreateDeviceId(store)
        assertEquals(first, second)
    }

    @Test
    fun blankStoredValueIsReplaced() {
        val store = FakeKeyValueStore()
        store.putString(StorageKeys.DEVICE_ID, "   ")
        val id = getOrCreateDeviceId(store)
        assertTrue(id.isNotBlank() && id != "   ")
    }

    @Test
    fun generatedIdHasUuidV4Shape() {
        val id = randomUuidString()
        assertTrue(
            Regex("[0-9a-f]{8}-[0-9a-f]{4}-4[0-9a-f]{3}-[89ab][0-9a-f]{3}-[0-9a-f]{12}").matches(id),
            "unexpected uuid shape: $id"
        )
    }
}
