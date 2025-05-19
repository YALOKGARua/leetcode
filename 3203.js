/**
 * @param {number[][]} edges1
 * @param {number[][]} edges2
 * @return {number}
 */
var minimumDiameterAfterMerge = function(edges1, edges2) {
    const n = edges1.length + 1;
    const m = edges2.length + 1;
    const graph1 = Array(n).fill().map(() => []);
    const graph2 = Array(m).fill().map(() => []);
    
    for (const [a, b] of edges1) {
        graph1[a].push(b);
        graph1[b].push(a);
    }
    
    for (const [a, b] of edges2) {
        graph2[a].push(b);
        graph2[b].push(a);
    }
    
    const dist1FromArbitrary = bfs(graph1, 0);
    const end1Tree1 = dist1FromArbitrary.indexOf(Math.max(...dist1FromArbitrary));
    const dist1FromEnd1 = bfs(graph1, end1Tree1);
    const end2Tree1 = dist1FromEnd1.indexOf(Math.max(...dist1FromEnd1));
    const diameter1 = dist1FromEnd1[end2Tree1];
    const dist2FromArbitrary = bfs(graph2, 0);
    const end1Tree2 = dist2FromArbitrary.indexOf(Math.max(...dist2FromArbitrary));
    const dist2FromEnd1 = bfs(graph2, end1Tree2);
    const end2Tree2 = dist2FromEnd1.indexOf(Math.max(...dist2FromEnd1));
    const diameter2 = dist2FromEnd1[end2Tree2];
    const distFromEnd1Tree1 = bfs(graph1, end1Tree1);
    const distFromEnd2Tree1 = bfs(graph1, end2Tree1);
    const distFromEnd1Tree2 = bfs(graph2, end1Tree2);
    const distFromEnd2Tree2 = bfs(graph2, end2Tree2);
    const radius1 = Math.floor(diameter1 / 2);
    const radius2 = Math.floor(diameter2 / 2);
    const possibleCenters1 = [];
    const possibleCenters2 = [];
    
    for (let i = 0; i < n; i++) {
        if (Math.max(distFromEnd1Tree1[i], distFromEnd2Tree1[i]) <= radius1 + 2) {
            possibleCenters1.push(i);
        }
    }
    
    for (let j = 0; j < m; j++) {
        if (Math.max(distFromEnd1Tree2[j], distFromEnd2Tree2[j]) <= radius2 + 2) {
            possibleCenters2.push(j);
        }
    }
    
    let minDiameter = Infinity;
    const centers1 = possibleCenters1.length > 50 ? possibleCenters1.slice(0, 50) : possibleCenters1;
    const centers2 = possibleCenters2.length > 50 ? possibleCenters2.slice(0, 50) : possibleCenters2;
    
    for (const i of centers1) {
        for (const j of centers2) {
            const path1 = distFromEnd1Tree1[i] + 1 + distFromEnd1Tree2[j];
            const path2 = distFromEnd1Tree1[i] + 1 + distFromEnd2Tree2[j];
            const path3 = distFromEnd2Tree1[i] + 1 + distFromEnd1Tree2[j];
            const path4 = distFromEnd2Tree1[i] + 1 + distFromEnd2Tree2[j];
            const longestPath = Math.max(path1, path2, path3, path4);
            const newDiameter = Math.max(diameter1, diameter2, longestPath);
            minDiameter = Math.min(minDiameter, newDiameter);
        }
    }
    
    return minDiameter;
};

function bfs(graph, start) {
    const n = graph.length;
    const distances = new Array(n).fill(-1);
    distances[start] = 0;
    
    const queue = [start];
    
    while (queue.length > 0) {
        const node = queue.shift();
        
        for (const neighbor of graph[node]) {
            if (distances[neighbor] === -1) {
                distances[neighbor] = distances[node] + 1;
                queue.push(neighbor);
            }
        }
    }
    
    return distances;
} 