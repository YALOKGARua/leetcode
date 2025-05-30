/*
 * @lc app=leetcode id=2197 lang=typescript
 *
 * [2197] Replace Non-Coprime Numbers in Array
 */

// @lc code=start
function replaceNonCoprimes(nums: number[]): number[] {
    const g = (a: number, b: number): number => b ? g(b, a % b) : a
    const l = (a: number, b: number): number => a / g(a, b) * b
    const st: number[] = []
    for (let x of nums) {
        while (st.length && g(st[st.length - 1], x) > 1) x = l(st.pop()!, x)
        st.push(x)
    }
    return st
}
// @lc code=end

