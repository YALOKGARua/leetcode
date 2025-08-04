#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

int main() {
    int n;
    cin >> n;
    
    vector<double> r(n);
    for (int i = 0; i < n; i++) {
        cin >> r[i];
    }
    
    double total = 0.0;
    
    for (int i = 0; i < n; i++) {
        double light = 1.0;
        for (int j = 0; j < i; j++) {
            light *= (1.0 - r[j]);
        }
        
        total += light * r[i];
        
        if (i < n - 1) {
            double through = light * (1.0 - r[i]);
            
            for (int j = i + 1; j < n; j++) {
                for (int k = i + 1; k < j; k++) {
                    through *= (1.0 - r[k]);
                }
                
                double bounce = through * r[j];
                
                double back = bounce;
                for (int k = j - 1; k >= i; k--) {
                    back *= (1.0 - r[k]);
                }
                
                double multiplier = 1.0;
                for (int k = i; k < j; k++) {
                    multiplier *= (1.0 - r[k]) * (1.0 - r[k]);
                }
                
                if (multiplier < 1.0) {
                    total += back / (1.0 - multiplier);
                } else {
                    total += back;
                }
                
                through *= (1.0 - r[j]);
            }
        }
    }
    
    cout << fixed << setprecision(4) << total << endl;
    
    return 0;
}
