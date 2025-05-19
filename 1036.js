/**
 * @param {number[][]} blocked
 * @param {number[]} source
 * @param {number[]} target
 * @return {boolean}
 */
var isEscapePossible = function(blocked, source, target) {
    const blockedSet = new Set(blocked.map(([x, y]) => `${x},${y}`));
    const LIMIT = 20000;
    
    return canEscape(source, target) && canEscape(target, source);
    
    function canEscape(start, end) {
        const queue = [start];
        const visited = new Set([`${start[0]},${start[1]}`]);
        const dirs = [[0, 1], [1, 0], [0, -1], [-1, 0]];
        
        while (queue.length && visited.size < LIMIT) {
            const [x, y] = queue.shift();
            
            if (x === end[0] && y === end[1]) return true;
            
            for (const [dx, dy] of dirs) {
                const nx = x + dx;
                const ny = y + dy;
                const key = `${nx},${ny}`;
                
                if (nx >= 0 && nx < 1e6 && ny >= 0 && ny < 1e6 && 
                    !blockedSet.has(key) && !visited.has(key)) {
                    queue.push([nx, ny]);
                    visited.add(key);
                }
            }
        }
        return visited.size >= LIMIT || visited.has(`${end[0]},${end[1]}`);
    }
}; 