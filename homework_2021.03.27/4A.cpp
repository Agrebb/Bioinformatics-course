#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <algorithm>

using namespace std;

map<char, int> inv_letters{{'A', 0}, {'C', 1}, {'G', 2}, {'U', 3}};
char rna_codon_table[64];

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

    string s; cin >> s;
    for (int i = 0; i < s.length(); i+=3){
        int x0 = inv_letters[s[i]], x1 = inv_letters[s[i+1]], x2 = inv_letters[s[i+2]];
        char codon = rna_codon_table[(x0 << 4) + (x1 << 2) + x2];
        if (codon != 0) cout << codon;
    }

    return 0;
}
