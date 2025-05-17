impl Solution {
    pub fn min_swaps(s: String) -> i32 {
        let chars: Vec<char> = s.chars().collect();
        let n = chars.len();
        
        let count_zeros = chars.iter().filter(|&&c| c == '0').count();
        let count_ones = n - count_zeros;
        
        if (count_zeros as i32 - count_ones as i32).abs() > 1 {
            return -1;
        }
        
        if count_zeros > count_ones {
            return count_mismatches(&chars, '0');
        } else if count_ones > count_zeros {
            return count_mismatches(&chars, '1');
        } else {
            return std::cmp::min(
                count_mismatches(&chars, '0'),
                count_mismatches(&chars, '1')
            );
        }
    }
}

fn count_mismatches(chars: &[char], start: char) -> i32 {
    let mut expected = start;
    let mut mismatches = 0;
    
    for &c in chars {
        if c != expected {
            mismatches += 1;
        }
        expected = if expected == '0' { '1' } else { '0' };
    }
    
    mismatches / 2
} 