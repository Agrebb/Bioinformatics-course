#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <queue>

using namespace std;
map <char, int> mass_spectrum_table;

map <int, int> mass_spectrum(string s, bool cyclic){
    int n = s.length();
    vector <int> spectrum(n, 0);
    map <int, int> ans;

    ans[0]++;
    for (int i = 0; i < n - 1; i++){
        vector <int> new_spectrum(n);
        for (int j = cyclic ? 0 : i; j < n; j++){
            new_spectrum[j] = spectrum[(j+n-1)%n] + mass_spectrum_table[s[j]];
            ans[new_spectrum[j]]++;
        }
        spectrum = new_spectrum;
    }
    int summ = 0;
    for (char c : s) summ += mass_spectrum_table[c];
    ans[summ]++;

    return ans;
}

int main(){
    freopen("../input.txt", "r", stdin);
    freopen("../output.txt", "w", stdout);

    //reading mass spectrum table from the same input file
    const int table_size = 18;
    for (int i = 0; i < table_size; i++){
        char c;
        int mass;
        cin >> c >> mass;
        mass_spectrum_table[c] = mass;
    }

    int new_mass;
    map<int, int> ideal_spectrum;
    while (cin >> new_mass){
        ideal_spectrum[new_mass]++;
    }

    set <string> final_peptides;
    queue <string> q;
    q.push("");
    while (!q.empty()){
        string s = q.front();
        q.pop();
        for (auto [c, m] : mass_spectrum_table){
            auto spectrum = mass_spectrum(s + c, false);
            auto cyclic_spectrum = mass_spectrum(s + c, true);

            bool ok = true, eq = true;
            for (auto [mass, cnt] : spectrum){
                if (ideal_spectrum[mass] < cnt) ok = false;
            }
            for (auto [mass, cnt] : cyclic_spectrum){
                if (ideal_spectrum[mass] != cnt) eq = false;
            }
            for (auto [mass, cnt] : ideal_spectrum){
                if (cyclic_spectrum[mass] != cnt) eq = false;
            }
            if (eq) final_peptides.insert(s + c);
            else if (ok) q.push(s + c);
        }
    }
    for (string s : final_peptides){
        for (int i = 0; i < s.length(); i++){
            if (i > 0) cout << "-";
            cout << mass_spectrum_table[s[i]];
        }
        cout << " ";
    }

    return 0;
}
