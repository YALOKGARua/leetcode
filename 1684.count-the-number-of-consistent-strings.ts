function countConsistentStrings(allowed: string, words: string[]): number {
    const s = new Set(allowed)
    return words.reduce((a, w) => a + Number([...w].every(c => s.has(c))), 0)
} 