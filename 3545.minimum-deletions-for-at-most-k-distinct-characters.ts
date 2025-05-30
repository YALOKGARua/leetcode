/*
 * @lc app=leetcode id=3545 lang=typescript
 *
 * [3545] Minimum Deletions for At Most K Distinct Characters
 */

// @lc code=start
function minDeletion(s: string, k: number): number {
    const f = Object.values([...s].reduce((a, c) => (a[c] = (a[c]||0)+1, a), {})).map(Number).sort((a, b) => a - b)
    return f.length <= k ? 0 : f.slice(0, f.length - k).reduce((a, b) => a + b, 0)
}
// @lc code=end

