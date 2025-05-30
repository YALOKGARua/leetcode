/*
 * @lc app=leetcode id=2256 lang=typescript
 *
 * [2256] Minimum Average Difference
 */

// @lc code=start
function minimumAverageDifference(nums: number[]): number {
    let n = nums.length, s = nums.reduce((a, b) => a + b), l = 0, d = 1e18, r = 0
    for (let i = 0; i < n; i++) {
        l += nums[i]
        let x = Math.floor(l / (i + 1)), y = i < n - 1 ? Math.floor((s - l) / (n - i - 1)) : 0
        let diff = Math.abs(x - y)
        if (diff < d) d = diff, r = i
    }
    return r
}
// @lc code=end

