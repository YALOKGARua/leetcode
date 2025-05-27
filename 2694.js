class EventEmitter {
    constructor() {
        this.e = new Map
        this.s = []
    }
    subscribe(k, f) {
        this.e.has(k) || this.e.set(k, [])
        this.e.get(k).push(f)
        let i = this.s.push([k, f]) - 1
        return { unsubscribe: () => {
            let [a, b] = this.s[i] || []
            if (!a) return
            let arr = this.e.get(a)
            arr.splice(arr.indexOf(b), 1)
            this.s[i] = 0
        }}
    }
    emit(k, a = []) {
        return (this.e.get(k) || []).map(f => f(...a))
    }
} 