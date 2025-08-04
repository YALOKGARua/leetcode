#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <cmath>
using namespace std;

int main() {
    int s, h, flow, n;
    cin >> s >> h >> flow >> n;
    
    vector<pair<int, int>> leaks;
    for(int i = 0; i < n; i++) {
        int height, leak_flow;
        cin >> height >> leak_flow;
        leaks.push_back({height, leak_flow});
    }
    
    sort(leaks.begin(), leaks.end());
    
    double volume = (double)s * h / 1000.0;
    double current_height = 0;
    double current_volume = 0;
    double total_seconds = 0;
    
    for(const auto& leak : leaks) {
        int leak_height = leak.first;
        int leak_flow = leak.second;
        
        if(current_height >= leak_height) continue;
        
        double height_to_fill = leak_height - current_height;
        double volume_to_fill = height_to_fill * s / 1000.0;
        
        double net_flow = flow;
        for(const auto& active_leak : leaks) {
            if(active_leak.first <= current_height) {
                net_flow -= active_leak.second;
            }
        }
        
        if(net_flow <= 0) {
            cout << "Impossible, " << (int)current_height << " cm." << endl;
            return 0;
        }
        
        double time_needed = volume_to_fill / net_flow * 60;
        total_seconds += time_needed;
        current_height = leak_height;
        current_volume += volume_to_fill;
    }
    
    double remaining_volume = volume - current_volume;
    double net_flow = flow;
    for(const auto& leak : leaks) {
        net_flow -= leak.second;
    }
    
    if(net_flow <= 0) {
        cout << "Impossible, " << (int)current_height << " cm." << endl;
        return 0;
    }
    
    double final_time = remaining_volume / net_flow * 60;
    total_seconds += final_time;
    
    int t = (int)floor(total_seconds);
    int hours = t / 3600;
    int minutes = (t % 3600) / 60;
    int seconds = t % 60;
    
    cout << setfill('0') << setw(2) << hours << ":" 
         << setfill('0') << setw(2) << minutes << ":" 
         << setfill('0') << setw(2) << seconds << endl;
    
    return 0;
}