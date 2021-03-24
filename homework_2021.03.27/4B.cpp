#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <algorithm>

using namespace std;

map<char, int> inv_letters{{'A', 0}, {'C', 1}, {'G', 2}, {'T', 3}};
map<char, char> invert{{'A', 'T'}, {'T', 'A'}, {'C', 'G'}, {'G', 'C'}};
char rna_codon_table[64];

string encode (string & s){
    string res;
    for (int j = 0; j < s.length(); j+=3){
        int x0 = inv_letters[s[j]], x1 = inv_letters[s[j+1]], x2 = inv_letters[s[j+2]];
        res.push_back(rna_codon_table[(x0 << 4) + (x1 << 2) + x2]);
    }
    return res;
}

int main(){
    freopen("../input.txt", "r", stdin);
    freopen("../output.txt", "w", stdout);

    //reading rna codon table from the same input file
    for (int i = 0; i < 64; i++){
        string s;
        getline(cin, s);
        if (s.length() == 5) rna_codon_table[i] = s[4];
        else rna_codon_table[i] = 0;
    }

    string s, t; cin >> s >> t;
    for (int i = 0; i <= s.length() - 3*t.length(); i++){
        string sub_s;
        for (int j = 0; j < 3*t.length(); j++) sub_s.push_back(s[i+j]);
        string res = encode(sub_s);

        string sub_reversed = sub_s;
        reverse(sub_reversed.begin(), sub_reversed.end());
        for (int j = 0; j < 3*t.length(); j++) sub_reversed[j] = invert[sub_reversed[j]];
        string res_reversed = encode(sub_reversed);

        if (res == t || res_reversed == t){
            cout << sub_s << "\n";
        }
    }
    return 0;
}
