/*
 * @lc app=leetcode id=1608 lang=typescript
 *
 * [1608] Special Array With X Elements Greater Than or Equal X
 */

// @lc code=start
function specialArray(nums: number[]): number {
    nums.sort((a, b) => a - b)
    for (let x = 1; x <= nums.length; x++) if (nums[nums.length - x] >= x && (nums.length - x === 0 || nums[nums.length - x - 1] < x)) return x
    return -1
}
// @lc code=end

