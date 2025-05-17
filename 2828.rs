impl Solution {
    pub fn is_acronym(words: Vec<String>, s: String) -> bool {
        if words.len() != s.len() {
            return false;
        }
        
        for (i, word) in words.iter().enumerate() {
            if let Some(first_char) = word.chars().next() {
                if first_char != s.chars().nth(i).unwrap() {
                    return false;
                }
            } else {
                return false;
            }
        }
        
        true
    }
} 