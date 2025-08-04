#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

unordered_map<string, string> build_codon_table() {
    string data =
        "UUU F CUU L AUU I GUU V UUC F CUC L AUC I GUC V "
        "UUA L CUA L AUA I GUA V UUG L CUG L AUG M GUG V "
        "UCU S CCU P ACU T GCU A UCC S CCC P ACC T GCC A "
        "UCA S CCA P ACA T GCA A UCG S CCG P ACG T GCG A "
        "UAU Y CAU H AAU N GAU D UAC Y CAC H AAC N GAC D "
        "UAA Stop CAA Q AAA K GAA E UAG Stop CAG Q AAG K GAG E "
        "UGU C CGU R AGU S GGU G UGC C CGC R AGC S GGC G "
        "UGA Stop CGA R AGA R GGA G UGG W CGG R AGG R GGG G";
    unordered_map<string, string> table;
    for (size_t i = 0; i < data.size();) {
        string codon = data.substr(i, 3);
        i += 4;
        string aa;
        while (i < data.size() && data[i] != ' ') aa += data[i++];
        ++i;
        table[codon] = aa;
    }
    return table;
}

vector<string> translate(const string& rna, const unordered_map<string, string>& table) {
    vector<string> results;
    for (int frame = 0; frame < 3; ++frame) {
        string seq, best;
        bool open = false;
        vector<string> all;
        for (int i = frame; i + 2 < rna.size(); i += 3) {
            string codon = rna.substr(i, 3);
            string aa = table.at(codon);
            if (!open && codon == "AUG") { open = true; seq = "M"; }
            else if (open && (codon == "UAA" || codon == "UAG" || codon == "UGA")) {
                all.push_back(seq);
                open = false;
            }
            else if (open && aa != "Stop") seq += aa;
        }
        if (!all.empty()) {
            string joined = all[0];
            for (int i = 1; i < all.size(); ++i) joined += "-" + all[i];
            results.push_back(joined);
        }
    }
    if (results.empty()) return {""};
    return {*max_element(results.begin(), results.end(), [](const string& a, const string& b) {
        return count_if(a.begin(), a.end(), ::isupper) < count_if(b.begin(), b.end(), ::isupper);
    })};
}

int main() {
    auto table = build_codon_table();
    int n;
    cin >> n; cin.ignore();
    for (int i = 0; i < n; i++) {
        string rna;
        getline(cin, rna);
        cout << translate(rna, table)[0] << endl;
    }
} 