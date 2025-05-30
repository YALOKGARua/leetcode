function closestMeetingNode(edges: number[], node1: number, node2: number): number {
    const n = edges.length, d1 = Array(n).fill(-1), d2 = Array(n).fill(-1)
    for (let i = node1, d = 0; i !== -1 && d1[i] === -1; i = edges[i], d++) d1[i] = d
    for (let i = node2, d = 0; i !== -1 && d2[i] === -1; i = edges[i], d++) d2[i] = d
    let res = -1, min = 1e9
    for (let i = 0; i < n; i++) if (d1[i] !== -1 && d2[i] !== -1) {
        const m = Math.max(d1[i], d2[i])
        if (m < min || (m === min && i < res)) min = m, res = i
    }
    return res
} 