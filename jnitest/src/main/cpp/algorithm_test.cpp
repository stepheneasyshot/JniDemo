#include <jni.h>
#include <string>
#include <android/log.h>

// Android log function wrappers
static const char *kTAG = "ALGORITHM_TEST";
#define LOGI(...) \
  ((void)__android_log_print(ANDROID_LOG_INFO, kTAG, __VA_ARGS__))
#define LOGW(...) \
  ((void)__android_log_print(ANDROID_LOG_WARN, kTAG, __VA_ARGS__))
#define LOGE(...) \
  ((void)__android_log_print(ANDROID_LOG_ERROR, kTAG, __VA_ARGS__))


extern "C" JNIEXPORT void JNICALL
Java_com_stephen_jnitest_AlgorithmDemo_combineTwoArrays(JNIEnv *env, jobject) {
    LOGI("Java_com_stephen_jnitest_AlgorithmDemo_combineTwoArrays triggered");
    int a[] = {1, 2, 3, 4, 5};
    int b[] = {0,0,0};


}