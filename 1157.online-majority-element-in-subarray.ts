/*
 * @lc app=leetcode id=1157 lang=typescript
 *
 * [1157] Online Majority Element In Subarray
 */

// @lc code=start
class MajorityChecker {
    private arr: number[];
    private pos: Map<number, number[]>;

    constructor(arr: number[]) {
        this.arr = arr;
        this.pos = new Map();
        arr.forEach((v, i) => {
            if (!this.pos.has(v)) this.pos.set(v, []);
            this.pos.get(v)!.push(i);
        });
    }

    query(left: number, right: number, threshold: number): number {
        for (let t = 0; t < 20; t++) {
            const x = this.arr[Math.floor(Math.random() * (right - left + 1)) + left];
            const p = this.pos.get(x)!;
            const l = this.lower(p, left);
            const r = this.upper(p, right);
            if (r - l >= threshold) return x;
        }
        return -1;
    }

    private lower(a: number[], x: number) {
        let l = 0;
        let r = a.length;
        while (l < r) {
            let m = (l + r) >> 1;
            if (a[m] < x) l = m + 1;
            else r = m;
        }
        return l;
    }

    private upper(a: number[], x: number) {
        let l = 0;
        let r = a.length;
        while (l < r) {
            let m = (l + r) >> 1;
            if (a[m] <= x) l = m + 1;
            else r = m;
        }
        return l;
    }
}

/**
 * Your MajorityChecker object will be instantiated and called as such:
 * var obj = new MajorityChecker(arr)
 * var param_1 = obj.query(left,right,threshold)
 */
// @lc code=end

