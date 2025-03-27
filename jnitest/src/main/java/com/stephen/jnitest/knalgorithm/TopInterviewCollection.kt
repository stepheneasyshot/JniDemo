package com.stephen.jnitest.knalgorithm

import android.util.Log

class TopInterviewCollection {

    companion object {
        private const val TAG = "TopInterviewCollection"
    }

    /**
     * 给定一个未经排序的整数数组，找到最长且 连续递增的子序列，并返回该序列的长度。
     *
     * 连续递增的子序列 可以由两个下标 l 和 r（l < r）确定，如果对于每个 l <= i < r，都有 nums[i] < nums[i + 1] ，那么子序列 [nums[l], nums[l + 1], ..., nums[r - 1], nums[r]] 就是连续递增子序列。
     *
     *
     *
     * 示例 1：
     *
     * 输入：nums = [1,3,5,4,7]
     * 输出：3
     * 解释：最长连续递增序列是 [1,3,5], 长度为3。
     * 尽管 [1,3,5,7] 也是升序的子序列, 但它不是连续的，因为 5 和 7 在原数组里被 4 隔开。
     * 示例 2：
     *
     * 输入：nums = [2,2,2,2,2]
     * 输出：1
     * 解释：最长连续递增序列是 [2], 长度为1。
     *
     *
     * 提示：
     *
     * 1 <= nums.length <= 104
     * -109 <= nums[i] <= 109
     */
    fun findLengthOfLCIS(nums: IntArray = intArrayOf(1, 2, 3, 4, 2, 2, 3, 4, 5, 6, 7)): Int {
        var maxLenth = 0
        var start = 0
        var end = 0
        // 第一个value，第二个index
        var numberList = mutableListOf<Int>()
        nums.forEachIndexed { index, value ->
            if (index == 0) {
                numberList.add(value)
                maxLenth = 1
                return@forEachIndexed
            }
            if (value > numberList[numberList.size - 1]) {
                numberList.add(value)
                maxLenth = maxOf(maxLenth, numberList.size)
                end = index
            } else {
                start = index
                numberList.clear()
                numberList.add(value)
            }
        }
        Log.i(TAG, "maxLenth = $maxLenth")
        return maxLenth
    }

    /**
     *给你两个按 非递减顺序 排列的整数数组 nums1 和 nums2，另有两个整数 m 和 n ，分别表示 nums1 和 nums2 中的元素数目。
     *
     * 请你 合并 nums2 到 nums1 中，使合并后的数组同样按 非递减顺序 排列。
     *
     * 注意：最终，合并后数组不应由函数返回，而是存储在数组 nums1 中。为了应对这种情况，nums1 的初始长度为 m + n，其中前 m 个元素表示应合并的元素，后 n 个元素为 0 ，应忽略。nums2 的长度为 n 。
     *
     *
     *
     * 示例 1：
     *
     * 输入：nums1 = [1,2,3,0,0,0], m = 3, nums2 = [2,5,6], n = 3
     * 输出：[1,2,2,3,5,6]
     * 解释：需要合并 [1,2,3] 和 [2,5,6] 。
     * 合并结果是 [1,2,2,3,5,6] ，其中斜体加粗标注的为 nums1 中的元素。
     * 示例 2：
     *
     * 输入：nums1 = [1], m = 1, nums2 = [], n = 0
     * 输出：[1]
     * 解释：需要合并 [1] 和 [] 。
     * 合并结果是 [1] 。
     * 示例 3：
     *
     * 输入：nums1 = [0], m = 0, nums2 = [1], n = 1
     * 输出：[1]
     * 解释：需要合并的数组是 [] 和 [1] 。
     * 合并结果是 [1] 。
     * 注意，因为 m = 0 ，所以 nums1 中没有元素。nums1 中仅存的 0 仅仅是为了确保合并结果可以顺利存放到 nums1 中。
     *
     *
     * 提示：
     *
     * nums1.length == m + n
     * nums2.length == n
     * 0 <= m, n <= 200
     * 1 <= m + n <= 200
     * -109 <= nums1[i], nums2[j] <= 109
     *
     *
     * 进阶：你可以设计实现一个时间复杂度为 O(m + n) 的算法解决此问题吗？
     */
    fun combineTwoArrayUsingKotlin(
        nums1: IntArray = intArrayOf(1, 2, 3, 0, 0, 0),
        m: Int = nums1.size,
        nums2: IntArray = intArrayOf(2, 5, 6),
        n: Int = nums2.size
    ) {
        val newNumArray = nums1 + nums2
        newNumArray.sort()
        Log.i(TAG, "newNumArray = ${newNumArray.contentToString()}")
    }
}