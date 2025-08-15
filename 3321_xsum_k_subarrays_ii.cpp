#include <vector>
#include <unordered_map>
#include <set>

using std::vector;
using std::unordered_map;
using std::multiset;

class Solution {
public:
	vector<long long> findXSum(vector<int>& nums, int k, int x) {
		struct Cmp {
			bool operator()(const std::pair<int,int>& a, const std::pair<int,int>& b) const {
				if (a.first != b.first) return a.first < b.first;
				return a.second < b.second;
			}
		};
		auto lessRank = [](const std::pair<int,int>& a, const std::pair<int,int>& b){
			if (a.first != b.first) return a.first < b.first;
			return a.second < b.second;
		};
		multiset<std::pair<int,int>, Cmp> in, out;
		unordered_map<int,int> freq;
		auto erasePair = [&](int f, int v){
			auto it = in.find({f, v});
			if (it != in.end()) { sumIn -= 1LL * it->first * it->second; in.erase(it); return; }
			auto jt = out.find({f, v});
			if (jt != out.end()) out.erase(jt);
		};
		auto moveMinInToOut = [&](){
			auto it = in.begin();
			sumIn -= 1LL * it->first * it->second;
			out.insert(*it);
			in.erase(it);
		};
		auto moveMaxOutToIn = [&](){
			auto it = std::prev(out.end());
			sumIn += 1LL * it->first * it->second;
			in.insert(*it);
			out.erase(it);
		};
		auto rebalance = [&](){
			while ((int)in.size() > x) moveMinInToOut();
			while ((int)in.size() < x && !out.empty()) moveMaxOutToIn();
			while (!in.empty() && !out.empty()) {
				auto a = *in.begin();
				auto b = *std::prev(out.end());
				if (!lessRank(a, b)) break;
				moveMinInToOut();
				moveMaxOutToIn();
			}
		};
		auto addValue = [&](int v){
			int f0 = freq[v];
			if (f0 > 0) erasePair(f0, v);
			int f = f0 + 1;
			freq[v] = f;
			in.insert({f, v});
			sumIn += 1LL * f * v;
			rebalance();
		};
		auto removeValue = [&](int v){
			int f0 = freq[v];
			erasePair(f0, v);
			if (f0 == 1) {
				freq.erase(v);
				rebalance();
				return;
			}
			int f = f0 - 1;
			freq[v] = f;
			in.insert({f, v});
			sumIn += 1LL * f * v;
			rebalance();
		};
		sumIn = 0;
		int n = (int)nums.size();
		vector<long long> ans;
		ans.reserve(n - k + 1);
		for (int i = 0; i < k; ++i) addValue(nums[i]);
		ans.push_back(sumIn);
		for (int i = k; i < n; ++i) {
			removeValue(nums[i - k]);
			addValue(nums[i]);
			ans.push_back(sumIn);
		}
		return ans;
	}

private:
	long long sumIn;
};