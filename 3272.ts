function countGoodIntegers(n: number, k: number): number {
    function factorial(x: number): number {
        let res = 1;
        for (let i = 2; i <= x; ++i) res *= i;
        return res;
    }
    function countPerms(digits: string[]): number {
        let map: Record<string, number> = {};
        for (let d of digits) map[d] = (map[d] || 0) + 1;
        let res = factorial(digits.length);
        for (let v of Object.values(map)) res /= factorial(v);
        if (map['0']) {
            map['0']--;
            let bad = factorial(digits.length - 1);
            for (let v of Object.values(map)) bad /= factorial(v);
            res -= bad;
        }
        return res;
    }
    let seen = new Set<string>();
    let half = Math.floor((n + 1) / 2);
    let start = Math.pow(10, half - 1);
    let end = Math.pow(10, half);
    let res = 0;
    for (let i = start; i < end; ++i) {
        let s = i.toString();
        let rev = s.split('').reverse().join('');
        let pal = n % 2 === 0 ? s + rev : s + rev.slice(1);
        if (pal[0] === '0' || parseInt(pal) % k !== 0) continue;
        let digits = pal.split('').sort().join('');
        if (seen.has(digits)) continue;
        seen.add(digits);
        res += countPerms(pal.split(''));
    }
    return res;
}
