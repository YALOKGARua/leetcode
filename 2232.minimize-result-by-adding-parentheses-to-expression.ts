/*
 * @lc app=leetcode id=2232 lang=typescript
 *
 * [2232] Minimize Result by Adding Parentheses to Expression
 */

// @lc code=start
function minimizeResult(expression: string): string {
    const [l, r] = expression.split('+')
    let min = 1e18, res = ''
    for (let i = 0; i < l.length; i++)
        for (let j = 1; j <= r.length; j++) {
            const a = l.slice(0, i), b = l.slice(i), c = r.slice(0, j), d = r.slice(j)
            const val = (a ? +a : 1) * (+b + +c) * (d ? +d : 1)
            const s = `${a}(${b}+${c})${d}`
            if (val < min) min = val, res = s
        }
    return res
}
// @lc code=end

