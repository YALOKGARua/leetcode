impl Solution {
    pub fn count_days_together(arrive_alice: String, leave_alice: String, arrive_bob: String, leave_bob: String) -> i32 {
        let days_in_month = [31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31];
        
        let to_day_of_year = |date: &str| -> i32 {
            let month: usize = date[0..2].parse().unwrap();
            let day: i32 = date[3..5].parse().unwrap();
            
            let mut total_days = 0;
            for i in 0..(month - 1) {
                total_days += days_in_month[i];
            }
            total_days + day
        };
        
        let arrive_alice_day = to_day_of_year(&arrive_alice);
        let leave_alice_day = to_day_of_year(&leave_alice);
        let arrive_bob_day = to_day_of_year(&arrive_bob);
        let leave_bob_day = to_day_of_year(&leave_bob);
        
        let start_day = arrive_alice_day.max(arrive_bob_day);
        let end_day = leave_alice_day.min(leave_bob_day);
        
        (end_day - start_day + 1).max(0)
    }
} 