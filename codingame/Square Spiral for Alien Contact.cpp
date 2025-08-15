#include <bits/stdc++.h>
using namespace std;

static pair<char,int> parseToken(const string &s){
	char ch = s.empty() ? 'A' : s[0];
	int val = 1;
	if(s.size() > 1) val = stoi(s.substr(1));
	return {ch, val};
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n; string corner, dirStr, t1, t2;
	if(!(cin >> n >> corner >> dirStr >> t1 >> t2)) return 0;
	vector<string> grid(n, string(n, ' '));
	pair<char,int> a = parseToken(t1), b = parseToken(t2);
	int step = 0;
	if(b.first > a.first) step = 1; else if(b.first < a.first) step = -1; else step = 0;
	int x = 0, y = 0;
	if(corner == "topLeft") { x = 0; y = 0; }
	else if(corner == "topRight") { x = 0; y = n - 1; }
	else if(corner == "bottomRight") { x = n - 1; y = n - 1; }
	else { x = n - 1; y = 0; }
	int dir = 0;
	bool clockwise = (dirStr == "clockwise");
	if(corner == "topLeft") dir = clockwise ? 0 : 1;
	else if(corner == "topRight") dir = clockwise ? 1 : 2;
	else if(corner == "bottomRight") dir = clockwise ? 2 : 3;
	else dir = clockwise ? 3 : 0;
	int dx[4] = {0,1,0,-1};
	int dy[4] = {1,0,-1,0};
	char cur = a.first;
	int cnt1 = a.second, cnt2 = b.second;
	int curLimit = cnt1, used = 0, groupIdx = 1;
	bool exhausted = !(cur >= 'A' && cur <= 'Z');
	auto place = [&](){
		if(!exhausted && cur >= 'A' && cur <= 'Z') grid[x][y] = cur;
		++used;
		if(used >= curLimit){
			used = 0;
			++groupIdx;
			if(groupIdx == 2) cur = b.first; else if(groupIdx > 2) cur = static_cast<char>(cur + step);
			curLimit = (groupIdx % 2 == 1 ? cnt1 : cnt2);
			exhausted = !(cur >= 'A' && cur <= 'Z');
		}
	};
	vector<vector<char>> seen(n, vector<char>(n, 0));
	int total = n * n;
	for(int k=0;k<total;k++){
		place();
		seen[x][y] = 1;
		if(k + 1 == total) break;
		int nx = x + dx[dir];
		int ny = y + dy[dir];
		if(nx < 0 || ny < 0 || nx >= n || ny >= n || seen[nx][ny]){
			dir = (dir + (clockwise ? 1 : 3)) & 3;
			nx = x + dx[dir];
			ny = y + dy[dir];
		}
		x = nx; y = ny;
	}
	int m = min(n, 31);
	for(int i=0;i<m;i++){
		for(int j=0;j<m;j++) cout << grid[i][j];
		cout << "\n";
	}
	return 0;
}


