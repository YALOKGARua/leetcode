#include <string>
using namespace std;

class Solution {
public:
    string subStrHash(string s, int power, int modulo, int k, int hashValue) {
        int n = s.length();
        long long curHash = 0;
        long long powerK = 1;
        int res = 0;
        
        // Вычисляем power^(k-1)
        for (int i = 0; i < k-1; i++) {
            powerK = (powerK * power) % modulo;
        }
        
        // Вычисляем хеш для последних k символов
        for (int i = n-1; i >= n-k; i--) {
            curHash = (curHash * power + (s[i] - 'a' + 1)) % modulo;
        }
        
        if (curHash == hashValue) {
            res = n-k;
        }
        
        // Двигаемся справа налево
        for (int i = n-k-1; i >= 0; i--) {
            // Удаляем последний символ из окна
            curHash = (curHash - ((s[i+k] - 'a' + 1) * powerK) % modulo + modulo) % modulo;
            // Добавляем новый символ
            curHash = (curHash * power + (s[i] - 'a' + 1)) % modulo;
            
            if (curHash == hashValue) {
                res = i;
            }
        }
        
        return s.substr(res, k);
    }
}; 