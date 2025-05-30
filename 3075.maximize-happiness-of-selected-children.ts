/*
 * @lc app=leetcode id=3075 lang=typescript
 *
 * [3075] Maximize Happiness of Selected Children
 */

// @lc code=start
function maximumHappinessSum(happiness: number[], k: number): number {
    happiness.sort((a, b) => b - a)
    let res = 0
    for (let i = 0; i < k; i++) res += Math.max(0, happiness[i] - i)
    return res
}
// @lc code=end

