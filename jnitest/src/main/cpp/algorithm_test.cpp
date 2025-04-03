#include <jni.h>
#include <string>
#include <android/log.h>
#include <vector>
#include <cstdlib>
#include "single_linked_list.h"

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

/**
 * 我的数青蛙
 */
int myCountCroakOfFrogs(std::string croakOfFrogs) {
    int arrayLenth = croakOfFrogs.length() / 5 + 1;
    int frogsNumber = 0;
    // 检查字符串中五个字母数量是否相等
    int cCount = 0;
    int rCount = 0;
    int oCount = 0;
    int aCount = 0;
    int kCount = 0;
    char tempFrogsArray[arrayLenth][6];
    // 清空初始化
    for (int j = 0; j < arrayLenth; j++) {
        for (int k = 0; k < 6; k++) {
            tempFrogsArray[j][k] = '\0';
        }
    }
    // 遍历每一个字母，往临时二维数组里填充数据
    for (char croakOfFrog: croakOfFrogs) {
        // 遇到c，判断有没有满了的项，满了的话，清空重新接收，否则新开一个
        if (croakOfFrog == 'c') {
            cCount++;
            for (int j = 0; j < arrayLenth; j++) {
                if (std::string(tempFrogsArray[j]) == "croak") {
                    // 清空数组
                    for (int k = 0; k < 6; k++) {
                        tempFrogsArray[j][k] = '\0';
                    }
                    tempFrogsArray[j][0] = 'c';
                    break;
                }
                if (std::string(tempFrogsArray[j]).empty()) {
                    tempFrogsArray[j][0] = 'c';
                    break;
                }
            }
        } else if (croakOfFrog == 'r') {
            rCount++;
            for (int j = 0; j < arrayLenth; j++) {
                if (std::string(tempFrogsArray[j]) == "c") {
                    tempFrogsArray[j][1] = 'r';
                    break;
                }
            }
        } else if (croakOfFrog == 'o') {
            oCount++;
            for (int j = 0; j < arrayLenth; j++) {
                if (std::string(tempFrogsArray[j]) == "cr") {
                    tempFrogsArray[j][2] = 'o';
                    break;
                }
            }
        } else if (croakOfFrog == 'a') {
            aCount++;
            for (int j = 0; j < arrayLenth; j++) {
                if (std::string(tempFrogsArray[j]) == "cro") {
                    tempFrogsArray[j][3] = 'a';
                    break;
                }
            }
        } else if (croakOfFrog == 'k') {
            kCount++;
            for (int j = 0; j < arrayLenth; j++) {
                if (std::string(tempFrogsArray[j]) == "croa") {
                    tempFrogsArray[j][4] = 'k';
                    break;
                }
            }
        }
        // 检索数组里面满足croak的项数量
        int count = 0;
        for (int j = 0; j < arrayLenth; j++) {
            if (std::string(tempFrogsArray[j]) == "croak") {
                count++;
            }
        }
        frogsNumber = frogsNumber > count ? frogsNumber : count;
    }
    if (cCount != rCount || rCount != oCount || oCount != aCount || aCount != kCount) {
        frogsNumber = -1;
    }
    // 检查数组里面是否有不满足croak的项
    for (int j = 0; j < arrayLenth; j++) {
        if (!std::string(tempFrogsArray[j]).empty() && std::string(tempFrogsArray[j]) != "croak") {
            frogsNumber = -1;
            break;
        }
    }
    return frogsNumber;
}

/**
 * 大佬的数青蛙
 * 将青蛙分成 5 种：
 * 刚才发出了 c 的声音。
 * 刚才发出了 r 的声音。
 * 刚才发出了 o 的声音。
 * 刚才发出了 a 的声音。
 * 刚才发出了 k 的声音。
 * 遍历 croakOfFrogs，例如当前遍历到 r，那么就看看有没有青蛙刚才发出了 c 的声音，如果有，那么让它接着发出 r 的声音。换句话说，我们需要消耗一个 c，产生一个 r。
 * 遍历到 c 时，看看有没有青蛙刚才发出了 k 的声音，如果有，那么复用这只青蛙，让它接着发出 c 的声音，即 cnt['k']-- 和 cnt['c']++；如果没有这种青蛙，那么新产生一只青蛙发出 c 的声音，即 cnt['c']++。
 * 遍历到 r 时，看看有没有青蛙刚才发出了 c 的声音，如果有，那么复用这只青蛙，让它接着发出 r 的声音，即 cnt['c']-- 和 cnt['r']++；如果没有这种青蛙，由于题目要求青蛙必须从 c 开始蛙鸣，不能直接从 r 开始，所以返回 −1。
 * 遍历到 o,a,k 的情况类似 r，找到该字母在 croak 的上一个字母的 cnt 值，如果 cnt 值大于 0，那么将其减一，同时当前字母的 cnt 值加一；如果上一个字母的 cnt 值等于 0，那么就返回 −1。
 * 遍历结束后，所有青蛙必须在最后发出 k 的声音。如果有青蛙在最后发出的声音不是 k（也就是 cnt 值大于 0），那么返回 −1，否则返回 cnt[k]。
 */
int countCroakOfFrogs(const std::string &croakOfFrogs) {
    int ans = 0;
    int c = 0, r = 0, o = 0, a = 0, k = 0;
    for (char ch: croakOfFrogs) {
        if (ch == 'c') {
            k--;
            c++;
            if (k < ans) {
                ans = k;
            }
        } else if (ch == 'r') {
            c--;
            r++;
        } else if (ch == 'o') {
            r--;
            o++;
        } else if (ch == 'a') {
            o--;
            a++;
        } else if (ch == 'k') {
            a--;
            k++;
        }
        if (c < 0 || r < 0 || o < 0 || a < 0) {
            return -1;
        }
    }
    if (c != 0 || r != 0 || o != 0 || a != 0) {
        return -1;
    }
    return -ans;
}

extern "C" JNIEXPORT jint JNICALL
Java_com_stephen_jnitest_AlgorithmDemo_countCroakOfFrogs(JNIEnv *env, jobject) {
    LOGI("Java_com_stephen_jnitest_AlgorithmDemo_countCroakOfFrogs triggered");
    std::string croakOfFrogs = "croakroak";
    int number = myCountCroakOfFrogs(croakOfFrogs);
    int number2 = countCroakOfFrogs(croakOfFrogs);
    LOGI("number = %d", number);
    LOGI("number2 = %d", number2);
    return number;
}

extern "C" JNIEXPORT void JNICALL
Java_com_stephen_jnitest_AlgorithmDemo_linkedListTest(JNIEnv *env, jobject) {
    LOGI("Java_com_stephen_jnitest_AlgorithmDemo_LinkedListTest triggered");
    TestSingleLinkedList();
}

