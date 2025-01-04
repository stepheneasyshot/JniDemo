#include <jni.h>
#include <string>
#include <thread>
#include <android/log.h>

// Android log function wrappers
static const char *kTAG = "Stephen_JNI_TEST";
#define LOGI(...) \
  ((void)__android_log_print(ANDROID_LOG_INFO, kTAG, __VA_ARGS__))
#define LOGW(...) \
  ((void)__android_log_print(ANDROID_LOG_WARN, kTAG, __VA_ARGS__))
#define LOGE(...) \
  ((void)__android_log_print(ANDROID_LOG_ERROR, kTAG, __VA_ARGS__))

static JavaVM *gJvm;

void delay(int milliseconds) {
    std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}

extern "C" JNIEXPORT jstring JNICALL
Java_com_stephen_jnitest_JniUtils_hello(JNIEnv *env, jobject) {
    LOGW("Initialize JavaVM");
    // 先初始化一个全局的JavaVM对象，供后续多线程使用
    env->GetJavaVM(&gJvm);

    const char *hello = "Hello from C++";

    LOGI("This is my first time using android log in C++");
    LOGI("Hello String: [%s]", hello);

    return env->NewStringUTF(hello);
}

extern "C" JNIEXPORT jint JNICALL
Java_com_stephen_jnitest_JniUtils_add(JNIEnv *env, jobject, jint a, jint b) {
    return a + b;
}

extern "C" JNIEXPORT jchar JNICALL
Java_com_stephen_jnitest_JniUtils_calChar(JNIEnv *env, jobject, jchar a) {
    return a + 1;
}

extern "C" JNIEXPORT jint JNICALL
Java_com_stephen_jnitest_JniUtils_calArraySize(JNIEnv *env, jobject, jintArray array) {
    return env->GetArrayLength(array);
}

extern "C" JNIEXPORT jstring JNICALL
Java_com_stephen_jnitest_JniUtils_combineCharArray(JNIEnv *env, jobject, jcharArray charArray) {
    jchar *arrayElements = env->GetCharArrayElements(charArray, nullptr);
    return env->NewString(arrayElements, env->GetArrayLength(charArray));
}

extern "C" JNIEXPORT jstring JNICALL
Java_com_stephen_jnitest_JniUtils_combineTwoString(JNIEnv *env, jobject, jstring a, jstring b) {
    const char *cStrA = env->GetStringUTFChars(a, nullptr);
    const char *cStrB = env->GetStringUTFChars(b, nullptr);
    std::string calString = strcat(const_cast<char *>(cStrA), cStrB);
    env->ReleaseStringUTFChars(a, cStrA);
    return env->NewStringUTF(calString.c_str());
}

extern "C" JNIEXPORT jstring JNICALL
Java_com_stephen_jnitest_JniUtils_calStringToCplusString(JNIEnv *env, jobject, jstring a) {
    const char *str = env->GetStringUTFChars(a, nullptr);
    std::string calString = strcat(const_cast<char *>(str), " , this is a C++ string");
    env->ReleaseStringUTFChars(a, str);
    return env->NewStringUTF(calString.c_str());
}

extern "C" JNIEXPORT void JNICALL
Java_com_stephen_jnitest_JniUtils_triggerCplusReflax(JNIEnv *env, jobject) {
    LOGI("Trigger C++ reflex");
    jclass cls = env->FindClass("com/stephen/jnitest/JniUtils");
    if (cls == nullptr) {
        LOGE("Can not find class: com/stephen/jnitest/JniUtils");
        return;
    }
    //构造函数 id
    jmethodID java_construct_method_id = env->GetMethodID(cls, "<init>", "()V");
    if (java_construct_method_id == nullptr) {
        LOGE("Can not find method: <init>");
        return;
    }
    jmethodID mid = env->GetMethodID(cls, "methodForCplus", "()V");
    if (mid == nullptr) {
        LOGE("Can not find method: methodForCplus");
        return;
    }
    jobject obj = env->NewObject(cls, java_construct_method_id);
    env->CallVoidMethod(obj, mid);
    // 释放局部引用
    env->DeleteLocalRef(obj);
    env->DeleteLocalRef(cls);
}

extern "C" JNIEXPORT void JNICALL
Java_com_stephen_jnitest_JniUtils_cplusExceptionCatch(JNIEnv *env, jobject) {
    jclass cls = env->FindClass("com/stephen/jnitest/JniUtils");
    if (cls == nullptr) {
        LOGE("Can not find class: com/stephen/jnitest/JniUtils");
        return;
    }
    //构造函数 id
    jmethodID java_construct_method_id = env->GetMethodID(cls, "<init>", "()V");
    if (java_construct_method_id == nullptr) {
        LOGE("Can not find method: <init>");
        return;
    }
    jmethodID mid = env->GetMethodID(cls, "exceptionMethodForCplus", "()I");
    if (mid == nullptr) {
        LOGE("Can not find method: exceptionMethodForCplus");
        return;
    }
    jobject obj = env->NewObject(cls, java_construct_method_id);
    env->CallIntMethod(obj, mid);

    if (env->ExceptionCheck()) {
        jthrowable mThrowable = env->ExceptionOccurred();
        // 打印异常信息
        env->ExceptionDescribe();
        // 清除异常信息
        env->ExceptionClear();
        //如果调用了 ExceptionClear 后，异常还需要 Java 层处理，我们可以抛出一个新的异常给 Java 层
        jclass clazz_exception = env->FindClass("java/lang/Exception");
        env->ThrowNew(clazz_exception, "JNI抛出的异常！");
        // 释放局部引用
        env->DeleteLocalRef(clazz_exception);
        env->DeleteLocalRef(mThrowable);
    }
    // 释放局部引用
    env->DeleteLocalRef(obj);
    env->DeleteLocalRef(cls);
}

static int count = 0;
jobject gJavaObj = nullptr;
jmethodID gJavaMethod = nullptr;
bool mainThreadRunning = false;
bool subThreadRunning = false;

static void *subThread(void *arg) {
    subThreadRunning = true;
    JNIEnv *env;
    LOGE("nativeThreadExec");
    LOGE("The pthread id : %ld\n", pthread_self());
    //从全局的JavaVM中获取到环境变量
    gJvm->AttachCurrentThread(&env, nullptr);
    for (int i = 0; i < 5; i++) {
        env->CallVoidMethod(gJavaObj, gJavaMethod, count++);
        delay(100);
    }

    subThreadRunning = false;
    if (!mainThreadRunning) {
        env->DeleteGlobalRef(gJavaObj);
        LOGE("全局引用在子线程销毁");
    }
    gJvm->DetachCurrentThread();

    return nullptr;
}

extern "C" JNIEXPORT void JNICALL
Java_com_stephen_jnitest_JniUtils_cplusThreadTest(JNIEnv *env, jobject thiz) {
    mainThreadRunning = true;
    // 先获取到Java层的类
    gJavaObj = env->NewGlobalRef(thiz);
    jclass cls = env->GetObjectClass(thiz);
    // 全局引用
    gJavaMethod = env->GetMethodID(cls, "cplusThreadCall", "(I)V");
    if (gJavaMethod == nullptr) {
        LOGE("Can not find method: cplusThreadCall");
        return;
    }
    //开启子线程
    pthread_t thread;
    if (pthread_create(&thread, nullptr, subThread, nullptr) != 0) {
        LOGE("Can not create thread");
        return;
    }
    // 主线程循环调用
    for (int i = 0; i < 5; i++) {
        env->CallVoidMethod(gJavaObj, gJavaMethod, count++);
        delay(100);
    }
    mainThreadRunning = false;
    if (!subThreadRunning) {
        env->DeleteGlobalRef(gJavaObj);
        LOGE("全局引用在主线程销毁");
    }
}


/**
 * 3 完成动态注册的入口函数
 *  其内容基本固定
 */
JNIEXPORT jint JNI_OnLoad(JavaVM *vm, void *reserved) {
    LOGE("JNI_OnLoad");
    JNIEnv *env;
    if (vm->GetEnv(reinterpret_cast<void **>(&env), JNI_VERSION_1_6) != JNI_OK) {
        return JNI_ERR;
    }

    // Find your class. JNI_OnLoad is called from the correct class loader context for this to work.
    jclass c = env->FindClass("com/stephen/jnitest/JniUtils");
    if (c == nullptr) return JNI_ERR;

    // Register your class' native methods.
    static const JNINativeMethod methods[] = {
            {"add", "(II)I", (void *) Java_com_stephen_jnitest_JniUtils_add},
    };
    int rc = env->RegisterNatives(c, methods, sizeof(methods) / sizeof(JNINativeMethod));
    if (rc != JNI_OK) return rc;
    LOGE("JNI_OnLoad SUCCESS!");
    return JNI_VERSION_1_6;
}
