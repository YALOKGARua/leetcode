/*
 * @lc app=leetcode id=790 lang=typescript
 *
 * [790] Domino and Tromino Tiling
 */

// @lc code=start
function numTilings(n: number): number {
    const m = 1e9 + 7, f = [1, 1, 2]
    for (let i = 3; i <= n; i++) f[i] = (2 * f[i - 1] % m + f[i - 3]) % m
    return f[n]
}
// @lc code=end

