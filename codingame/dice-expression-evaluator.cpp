#include <iostream>
#include <iomanip>
#include <string>
#include <map>
#include <cctype>
using namespace std;

struct Dist {
    map<int, double> p;
    Dist() {}
    Dist(int v) { p[v] = 1.0; }
    Dist(int l, int r) { for(int i = l; i <= r; ++i) p[i] = 1.0/(r-l+1); }
};

Dist parseExpr(const string&, int&);
Dist parseCmp(const string&, int&);
Dist parseTerm(const string&, int&);
Dist parseFactor(const string&, int&);

Dist op(const Dist& a, const Dist& b, auto f) {
    Dist r;
    for(const auto& [x, px] : a.p) for(const auto& [y, py] : b.p)
        r.p[f(x, y)] += px * py;
    return r;
}

int parseNum(const string& s, int& i) {
    int v = 0;
    while(i < s.size() && isdigit(s[i])) v = v*10 + (s[i++]-'0');
    return v;
}

Dist parseDice(const string& s, int& i) { ++i; return Dist(1, parseNum(s, i)); }

Dist parseFactor(const string& s, int& i) {
    if(s[i] == '(') { ++i; auto d = parseCmp(s, i); ++i; return d; }
    if(s[i] == 'd') return parseDice(s, i);
    return Dist(parseNum(s, i));
}

Dist parseTerm(const string& s, int& i) {
    auto d = parseFactor(s, i);
    while(i < s.size() && s[i] == '*') d = op(d, parseFactor(s, ++i), [](int x, int y){return x*y;});
    return d;
}

Dist parseExpr(const string& s, int& i) {
    auto d = parseTerm(s, i);
    while(i < s.size() && (s[i] == '+' || s[i] == '-')) {
        char o = s[i++];
        auto t = parseTerm(s, i);
        d = (o == '+') ? op(d, t, [](int x, int y){return x+y;}) : op(d, t, [](int x, int y){return x-y;});
    }
    return d;
}

Dist parseCmp(const string& s, int& i) {
    auto d = parseExpr(s, i);
    while(i < s.size() && s[i] == '>') d = op(d, parseExpr(s, ++i), [](int x, int y){return x > y;});
    return d;
}

int main() {
    string s; getline(cin, s); int i = 0;
    auto d = parseCmp(s, i);
    for(const auto& [v, p] : d.p) cout << v << ' ' << fixed << setprecision(2) << p*100 << '\n';
} 