use std::collections::HashMap;

impl Solution {
    pub fn maximum_subarray_sum(nums: Vec<i32>, k: i32) -> i64 {
        let k = k as i64;
        let mut prefix_map: HashMap<i64, i64> = HashMap::new();
        let mut result: Option<i64> = None;
        let mut prefix_sum: i64 = 0;
        
        for i in 0..nums.len() {
            let num = nums[i] as i64;
            prefix_sum += num;
            
            if let Some(&prev_sum) = prefix_map.get(&(num - k)) {
                let curr_sum = prefix_sum - prev_sum;
                result = Some(result.map_or(curr_sum, |x| x.max(curr_sum)));
            }
            
            if let Some(&prev_sum) = prefix_map.get(&(num + k)) {
                let curr_sum = prefix_sum - prev_sum;
                result = Some(result.map_or(curr_sum, |x| x.max(curr_sum)));
            }

            let entry = prefix_map.entry(num).or_insert(prefix_sum - num);
            *entry = (*entry).min(prefix_sum - num);
        }
        
        result.unwrap_or(0)
    }
} 