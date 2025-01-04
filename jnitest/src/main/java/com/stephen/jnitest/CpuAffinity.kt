package com.stephen.jnitest

object CpuAffinity {

    fun init() {
        System.loadLibrary("cpu-affinity")
    }

    private external fun getCores(): Int

    private external fun bindThreadToCore(core: Int): Int

    private external fun bindPidToCore(pid: Int, core: Int): Int

    fun getCoresCount(): Int {
        return getCores()
    }

    fun threadToCore(core: Int, block: () -> Unit) {
        bindThreadToCore(core)
        block()
    }

    fun pidToCore(pid: Int, core: Int){
        bindPidToCore(pid, core)
    }

}
