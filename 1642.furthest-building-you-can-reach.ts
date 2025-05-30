/*
 * @lc app=leetcode id=1642 lang=typescript
 *
 * [1642] Furthest Building You Can Reach
 */

// @lc code=start
function furthestBuilding(heights: number[], bricks: number, ladders: number): number {
    const heap: number[] = []
    for (let i = 0; i < heights.length - 1; i++) {
        let d = heights[i + 1] - heights[i]
        if (d > 0) {
            let l = 0, r = heap.length
            while (l < r) {
                let m = (l + r) >> 1
                if (heap[m] < d) l = m + 1; else r = m
            }
            heap.splice(l, 0, d)
            if (heap.length > ladders) bricks -= heap.shift()!
            if (bricks < 0) return i
        }
    }
    return heights.length - 1
}
// @lc code=end

