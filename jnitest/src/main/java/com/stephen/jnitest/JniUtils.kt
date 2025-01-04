package com.stephen.jnitest

import android.util.Log
import androidx.annotation.Keep

@Keep
object JniUtils {

    const val TAG = "JniUtils"

    fun init() {
        Log.i(TAG, "init() Triggered")
        System.loadLibrary("jni-test")
    }

    external fun hello(): String

    fun testDataType() {
        Log.i(TAG, "add(1, 3) = ${add(1, 3)}")
        // ASCII基础上加一个1，应该为下一个字符
        Log.i(TAG, "calChar('a') = ${calChar('a')}")

        // 复杂数据类型
        val array = intArrayOf(1, 2, 3, 4, 5)
        Log.i(TAG, "calArraySize(array) = ${calArraySize(array)}")
        val charArray = charArrayOf('h', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd')
        Log.i(TAG, "combineCharArray(charArray) = ${combineCharArray(charArray)}")
        // 字符串
        val stringa = "hello"
        val stringb = " motherf**ker"
        Log.i(TAG, "combineTwoString(stringa, stringb) = ${combineTwoString(stringa, stringb)}")
        // 字符串加上C++的String
        val javaString = "This is a Java String"
        Log.i(TAG, "calStringToCplusString(javaString) = ${calStringToCplusString(javaString)}")

        // C++反射
        triggerCplusReflax()
        try {
            // C++异常处理
            cplusExceptionCatch()
        } catch (e: Exception) {
            Log.i(TAG, "exceptionMethodForCplus() = ${e.message}")
        }

        // C++多线程
        cplusThreadTest()
    }

    fun methodForCplus() {
        Log.i(TAG, "methodForCplus Triggered")
    }

    fun exceptionMethodForCplus(): Int = 20 / 0

    fun cplusThreadCall(count:Int) {
        Log.i(TAG, "cplusThreadCall Triggered ThreadName: ${Thread.currentThread().name}, count: $count")
    }

    external fun add(a: Int, b: Int): Int

    external fun calChar(charater: Char): Char

    external fun calArraySize(array: IntArray): Int

    external fun combineCharArray(charArray: CharArray): String

    external fun combineTwoString(stringa: String, stringb: String): String

    external fun calStringToCplusString(javaString: String): String

    external fun triggerCplusReflax()

    external fun cplusExceptionCatch()

    external fun cplusThreadTest()
}