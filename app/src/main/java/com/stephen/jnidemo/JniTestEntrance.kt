package com.stephen.jnidemo

import android.widget.Toast
import com.stephen.jnitest.CpuAffinity
import com.stephen.jnitest.ImageBlurUtils
import com.stephen.jnitest.JniUtils
import kotlinx.coroutines.MainScope
import kotlinx.coroutines.delay
import kotlinx.coroutines.launch
import java.lang.Thread.sleep
import kotlin.concurrent.thread

object JniTestEntrance {

    fun init() {

        ImageBlurUtils.init()

        MainScope().launch {
            // hello world
            JniUtils.init()
            delay(3000L)
            val jniString = JniUtils.hello()
            Toast.makeText(appContext, jniString, Toast.LENGTH_LONG).show()
            // 测试数据类型
            dataTypeTest()
        }

        // cpu亲和性测试
        cpuAffinity()
    }

    private var result: Long = 0L
    private fun cpuAffinity() {
        MainScope().launch {
            CpuAffinity.init()
            delay(1000L)
            CpuAffinity.threadToCore(5) {
                thread {
                    MainScope().launch {
                        Toast.makeText(
                            appContext,
                            "getCoresCount:${CpuAffinity.getCoresCount()}",
                            Toast.LENGTH_LONG
                        ).show()
                    }
                    Thread.currentThread().name = "calculateThread"
                    repeat(1_000_000) {
                        result ++
                    }
                    MainScope().launch {
                        Toast.makeText(
                            appContext,
                            "calculateThread result:$result",
                            Toast.LENGTH_LONG
                        ).show()
                    }
                    // 延时3s,使线程在trace文件中更明显
                    sleep(3000L)
                }
            }
        }
    }

    private fun dataTypeTest() {
        // 测试数据类型
        JniUtils.testDataType()
    }
}