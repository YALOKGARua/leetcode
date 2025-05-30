/*
 * @lc app=leetcode id=782 lang=typescript
 *
 * [782] Transform to Chessboard
 *
 * https://leetcode.com/problems/transform-to-chessboard/description/
 *
 * algorithms
 * Hard (50.53%)
 * Likes:    369
 * Dislikes: 312
 * Total Accepted:    19.6K
 * Total Submissions: 38.8K
 * Testcase Example:  '[[0,1,1,0],[0,1,1,0],[1,0,0,1],[1,0,0,1]]'
 *
 * You are given an n x n binary grid board. In each move, you can swap any two
 * rows with each other, or any two columns with each other.
 * 
 * Return the minimum number of moves to transform the board into a chessboard
 * board. If the task is impossible, return -1.
 * 
 * A chessboard board is a board where no 0's and no 1's are 4-directionally
 * adjacent.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: board = [[0,1,1,0],[0,1,1,0],[1,0,0,1],[1,0,0,1]]
 * Output: 2
 * Explanation: One potential sequence of moves is shown.
 * The first move swaps the first and second column.
 * The second move swaps the second and third row.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: board = [[0,1],[1,0]]
 * Output: 0
 * Explanation: Also note that the board with 0 in the top left corner, is also
 * a valid chessboard.
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: board = [[1,0],[1,0]]
 * Output: -1
 * Explanation: No matter what sequence of moves you make, you cannot end with
 * a valid chessboard.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * n == board.length
 * n == board[i].length
 * 2 <= n <= 30
 * board[i][j] is either 0 or 1.
 * 
 * 
 */

// @lc code=start
function movesToChessboard(b: number[][]): number {
    const n = b.length, r = b.map(x => x.join('')), c = b[0].map((_, j) => b.map(x => x[j]).join(''))
    const f = (a: string[]) => {
        const m = a[0], inv = [...m].map(x => 1 - +x).join('')
        if (!a.every(x => x === m || x === inv)) return -1
        const cnt = a.filter(x => x === m).length
        if (Math.abs(n - 2 * cnt) > 1) return -1
        let p1 = 0, p2 = 0
        for (let i = 0; i < n; i++) {
            if (a[i] !== (i % 2 ? inv : m)) p1++
            if (a[i] !== (i % 2 ? m : inv)) p2++
        }
        let s = n % 2 ? (cnt === Math.floor((n + 1) / 2) ? p1 : p2) : Math.min(p1, p2)
        return s / 2
    }
    const x = f(r), y = f(c)
    return x === -1 || y === -1 ? -1 : x + y
}
// @lc code=end