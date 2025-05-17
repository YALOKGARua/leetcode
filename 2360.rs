use std::collections::HashMap;

impl Solution {
    pub fn longest_cycle(edges: Vec<i32>) -> i32 {
        let n = edges.len();
        let mut visited = vec![false; n];
        let mut max_cycle_len = -1;
        
        for start in 0..n {
            if visited[start] {
                continue;
            }
            
            let mut curr = start;
            let mut node_time = HashMap::new();
            let mut time = 0;
            
            while curr != usize::MAX && !visited[curr] {
                visited[curr] = true;
                node_time.insert(curr, time);
                time += 1;
                
                let next = edges[curr];
                if next == -1 {
                    break;
                }
                
                curr = next as usize;
                
                if visited[curr] {
                    if let Some(&start_time) = node_time.get(&curr) {
                        max_cycle_len = max_cycle_len.max(time - start_time);
                    }
                    break;
                }
            }
        }
        
        max_cycle_len
    }
} 