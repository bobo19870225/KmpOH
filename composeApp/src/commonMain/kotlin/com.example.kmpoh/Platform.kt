package com.example.kmpoh

interface Platform {
    val name: String
}

expect fun getPlatform(): Platform

