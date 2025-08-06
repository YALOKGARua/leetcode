class Solution {
public:
    int minimizeSet(int divisor1, int divisor2, int uniqueCnt1, int uniqueCnt2) {
        long long left = 1, right = 1e18;
        while (left < right) {
            long long mid = left + (right - left) / 2;
            long long notDiv1 = mid - mid / divisor1;
            long long notDiv2 = mid - mid / divisor2;
            long long lcm = (long long)divisor1 * divisor2 / __gcd(divisor1, divisor2);
            long long notDivBoth = mid - mid / lcm;
            long long onlyDiv1 = mid / divisor1 - mid / lcm;
            long long onlyDiv2 = mid / divisor2 - mid / lcm;
            long long total = notDiv1 + notDiv2 - notDivBoth;
            if (notDiv1 >= uniqueCnt1 && notDiv2 >= uniqueCnt2 && total >= uniqueCnt1 + uniqueCnt2) {
                right = mid;
            } else {
                left = mid + 1;
            }
        }
        return (int)left;
    }
}; 