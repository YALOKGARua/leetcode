function countGoodIntegers(n: number, k: number): number {
    let res = 0
    const fact = [1]
    for (let i = 1; i <= n; i++) fact[i] = fact[i - 1] * i
    const gen = (a: number[], d: number, left: number) => {
        if (d === 10) {
            if (left !== 0 || a[0] > n - 1) return
            let odd = 0
            for (let x of a) odd += x % 2
            if (odd > 1) return
            let half: number[] = []
            for (let i = 0; i < 10; i++) for (let j = 0; j < (a[i] >> 1); j++) half.push(i)
            const mids: number[] = []
            for (let i = 0; i < 10; i++) if (a[i] % 2) mids.push(i)
            const set = new Set<string>()
            if (half.length === 0) {
                for (let m of mids.length ? mids : [null]) {
                    let p = m !== null ? String(m).repeat(n) : ''
                    if (p && p[0] !== '0' && +p % k === 0) res += fact[n] / a.reduce((x, y) => x * fact[y], 1)
                }
                return
            }
            half.sort()
            const next_perm = (arr: number[]) => {
                let i = arr.length - 2
                while (i >= 0 && arr[i] >= arr[i + 1]) i--
                if (i < 0) return false
                let j = arr.length - 1
                while (arr[j] <= arr[i]) j--
                [arr[i], arr[j]] = [arr[j], arr[i]]
                let l = i + 1, r = arr.length - 1
                while (l < r) [arr[l++], arr[r--]] = [arr[r], arr[l]]
                return true
            }
            let used = new Set<string>()
            do {
                if (half[0] === 0) continue
                let s = half.join(''), r = [...half].reverse().join('')
                for (let m of mids.length ? mids : [null]) {
                    let p = s + (m !== null ? m : '') + r
                    if (!used.has(p) && +p % k === 0) {
                        used.add(p)
                        res += fact[n] / a.reduce((x, y) => x * fact[y], 1)
                    }
                }
            } while (next_perm(half))
            return
        }
        for (let i = 0; i <= left; i++) { a[d] = i; gen(a, d + 1, left - i) }
    }
    gen(Array(10).fill(0), 0, n)
    return res
} 