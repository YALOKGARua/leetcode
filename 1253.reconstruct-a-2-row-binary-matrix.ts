/*
 * @lc app=leetcode id=1253 lang=typescript
 *
 * [1253] Reconstruct a 2-Row Binary Matrix
 */

// @lc code=start
function reconstructMatrix(upper: number, lower: number, colsum: number[]): number[][] {
    const n = colsum.length
    const res: number[][] = Array.from({ length: 2 }, () => Array(n).fill(0))
    for (let i = 0; i < n; i++) {
        if (colsum[i] === 2) {
            res[0][i] = 1
            res[1][i] = 1
            upper -= 1
            lower -= 1
        } else if (colsum[i] === 1) {
            if (upper > lower) {
                res[0][i] = 1
                upper -= 1
            } else {
                res[1][i] = 1   
                lower -= 1
            }
        }
    }
    return upper === 0 && lower === 0 ? res : []
}
// @lc code=end

