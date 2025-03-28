#include <jni.h>
#include <string>
#include <android/log.h>
#include <vector>
#include <cstdlib>

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
    int b[] = {0, 0, 0};
    int m = sizeof(a) / sizeof(a[0]);
    int n = sizeof(b) / sizeof(b[0]);
    int arrayCombined[m + n];
    for (int i = 0; i < m; i++) {
        arrayCombined[i] = a[i];
    }
    // 方案一 冒泡排序
//    for (int i = 0; i < n; i++) {
//        arrayCombined[m + i] = b[i];
//    }
//    for (int i = 0; i < m + n; i++) {
//        for (int j = 0; j < m + n - i - 1; j++) {
//            if (arrayCombined[j] > arrayCombined[j + 1]) {
//                int temp = arrayCombined[j];
//                arrayCombined[j] = arrayCombined[j + 1];
//                arrayCombined[j + 1] = temp;
//            }
//        }
//    }

    // 方案二 将第二个数组，按顺序插入这个临时数组中
    for (int i = 0; i < n; i++) {
        int j = m + i;
        // 从后往前遍历数组，找到所有小于等于b[i]的元素，往
        while (j > 0 && arrayCombined[j - 1] > b[i]) {
            // 将数组元素向后移动一位
            arrayCombined[j] = arrayCombined[j - 1];
            j--;
        }
        // 将b[i]插入到数组中正确位置
        arrayCombined[j] = b[i];
    }

    // 打印数组
    for (int i = 0; i < m + n; i++) {
        LOGI("%d", arrayCombined[i]);
    }
}

int removeElement(std::vector<int> &nums, int val) {
    int eraseCount = 0;
    if (nums.size() == 0) {
        return 0;
    }
    int removeOriginalIndexes[nums.size()];
    for (int i = 0; i < nums.size(); i++) {
        if (nums[i] == val) {
            removeOriginalIndexes[eraseCount] = i;
            eraseCount++;
        }
    }
    for (int i = 0; i < eraseCount; i++) {
        nums.erase(nums.begin() + removeOriginalIndexes[i] - i);
    }
    return nums.size();
}

extern "C" JNIEXPORT void JNICALL
Java_com_stephen_jnitest_AlgorithmDemo_removeElementTest(JNIEnv *env, jobject) {
    LOGI("Java_com_stephen_jnitest_AlgorithmDemo_removeElement triggered");
    std::vector<int> nums = {3, 2, 2, 1, 3, 3};
    int val = 3;
    removeElement(nums, val);


}