package com.stephen.jnitest

import android.util.Log
import com.stephen.jnitest.knalgorithm.TopInterviewCollection

object AlgorithmDemo {

    private const val TAG = "AlgorithmDemo"

    fun init() {
        System.loadLibrary("algorithm-demo")
    }

    fun kotlinVersion() {
        Log.i(TAG, "kotlinVersion")
        TopInterviewCollection().apply {
            findLengthOfLCIS()
            combineTwoArrayUsingKotlin()
        }
    }

    fun cppVersion() {
        Log.i(TAG, "cppVersion")
        combineTwoArrays()
        removeElementTest()
        bubbleSortTest()
        quickSortTest()
    }

    private external fun combineTwoArrays()

    private external fun removeElementTest()

    private external fun bubbleSortTest()

    private external fun quickSortTest()
}