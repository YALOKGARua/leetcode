#include <vector>
#include <string>
#include <algorithm>
using namespace std;

class Solution {
    bool isPalindrome(const string& s) {
        int l = 0, r = s.size() - 1;
        while (l < r) if (s[l++] != s[r--]) return false;
        return true;
    }
    string toBaseK(long long x, int k) {
        string res;
        while (x) {
            res += char('0' + x % k);
            x /= k;
        }
        reverse(res.begin(), res.end());
        return res;
    }
public:
    long long kMirror(int k, int n) {
        vector<long long> ans;
        for (int len = 1; ans.size() < n; ++len) {
            int half = (len + 1) / 2;
            long long start = pow(10, half - 1), end = pow(10, half);
            for (long long i = start; i < end; ++i) {
                string s = to_string(i);
                string t = s;
                if (len % 2) t.pop_back();
                reverse(t.begin(), t.end());
                long long num = stoll(s + t);
                if (isPalindrome(toBaseK(num, k))) ans.push_back(num);
                if (ans.size() == n) break;
            }
        }
        long long sum = 0;
        for (auto x : ans) sum += x;
        return sum;
    }
}; 