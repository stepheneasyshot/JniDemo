package com.stephen.jnidemo

import android.app.Application

class JniDemoApplication : Application() {

    companion object {
        lateinit var instance: JniDemoApplication
    }

    init {
        instance = this
    }

    override fun onCreate() {
        super.onCreate()
        JniTestEntrance.init()
    }
}

val appContext = JniDemoApplication.instance.applicationContext