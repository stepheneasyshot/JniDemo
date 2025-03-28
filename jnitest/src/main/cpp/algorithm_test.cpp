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


/**
 * 冒泡排序
 * 从前往后，每个元素都和后面的所有元素比较一次，将最小的元素移到前面来
 * @param arr
 * @param n
 */
void bubbleSort(std::vector<int> &arr) {
    for (int i = 0; i < arr.size(); i++) {
        for (int j = i; j < arr.size(); j++) {
            // 如果当前元素大于后面的元素，交换两个元素，将最小的元素移到前面来
            if (arr[i] > arr[j]) {
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
}

/**
 * 插入排序
 * 从前往后，取一个元素，和前面的所有元素比较一次，将这个元素插入到合适的位置
 */
void insertionSort(std::vector<int> &arr) {
    int n = arr.size();
    for (int i = 1; i < n; ++i) {
        int key = arr[i];
        int j = i - 1;
        // 将大于key的元素向后移动
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            --j;
        }
        arr[j + 1] = key;
    }
}

// 划分函数，选取一个基准元素，将数组分为两部分，走完之后，基准元素插入到其该在的位置.
// 其右侧所有元素都比基准元素大，左侧所有元素都比基准元素小
int partition(std::vector<int> &arr, int low, int high) {
    int base = arr[high];
    int baseIndex = low;
    // 遍历数组，将所有小于基准元素的元素都移动到基准元素的左侧
    for (int i = low; i <= high; i++) {
        if (arr[i] < base) {
            std::swap(arr[i], arr[baseIndex]);
            baseIndex++;
        }
    }
    // 将基准元素插入到其该在的位置
    std::swap(arr[high], arr[baseIndex]);
    return baseIndex;
}

// 递归快速排序，只要目标区域包含两个及以上的元素，就继续排序
void quickSort(std::vector<int> &arr, int low, int high) {
    if (low < high) {
        int baseIndex = partition(arr, low, high);
        quickSort(arr, low, baseIndex - 1);
        quickSort(arr, baseIndex + 1, high);
    }
}

extern "C" JNIEXPORT void JNICALL
Java_com_stephen_jnitest_AlgorithmDemo_quickSortTest(JNIEnv *env, jobject) {
    LOGI("Java_com_stephen_jnitest_AlgorithmDemo_quickSortTest triggered");
    std::vector<int> arr = {64, 34, 25, 12, 68, 81, 122, 22, 11, 90};
    quickSort(arr, 0, arr.size() - 1);
    for (int i: arr) {
        LOGI("quickSortTest -> %d", i);
    }
}

extern "C" JNIEXPORT void JNICALL
Java_com_stephen_jnitest_AlgorithmDemo_bubbleSortTest(JNIEnv *env, jobject) {
    LOGI("Java_com_stephen_jnitest_AlgorithmDemo_bubbleSortTest triggered");
    std::vector<int> arr = {64, 34, 25, 12, 68, 81, 122, 22, 11, 90};
    bubbleSort(arr);
    for (int i: arr) {
        LOGI("bubbleSortTest -> %d", i);
    }
}


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
//    bubbleSort(arrayCombined);

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
    if (nums.empty()) {
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
