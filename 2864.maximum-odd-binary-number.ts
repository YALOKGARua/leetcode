/*
 * @lc app=leetcode id=2864 lang=typescript
 *
 * [2864] Maximum Odd Binary Number
 */

// @lc code=start
function maximumOddBinaryNumber(s: string): string {
    const n = s.length
    let count = 0
    for (let i = 0; i < n; i++) {
        if (s[i] === '1') count++
    }
    return '1'.repeat(count - 1) + '0'.repeat(n - count) + '1'
}
// @lc code=end

