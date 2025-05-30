/*
 * @lc app=leetcode id=777 lang=typescript
 *
 * [777] Swap Adjacent in LR String
 */

// @lc code=start
function canTransform(start: string, result: string): boolean {
    if (start.replace(/X/g, '') !== result.replace(/X/g, '')) return false
    let i = 0, j = 0, n = start.length
    while (i < n && j < n) {
        while (i < n && start[i] === 'X') i++
        while (j < n && result[j] === 'X') j++
        if (i === n || j === n) break
        if (start[i] !== result[j] || (start[i] === 'L' && i < j) || (start[i] === 'R' && i > j)) return false
        i++
        j++
    }
    return true
}
// @lc code=end

