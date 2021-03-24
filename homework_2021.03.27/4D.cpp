#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <algorithm>

using namespace std;
map <char, int> mass_spectrum_table;

int main(){
    freopen("../input.txt", "r", stdin);
    freopen("../output.txt", "w", stdout);

    //reading mass spectrum table from the same input file
    const int table_size = 20;
    for (int i = 0; i < table_size; i++){
        char c;
        int mass;
        cin >> c >> mass;
        mass_spectrum_table[c] = mass;
    }

    string s;
    cin >> s;
    int n = s.length();
    vector <int> spectrum(n, 0);
    vector <int> ans;

    ans.push_back(0);
    for (int i = 0; i < n - 1; i++){
        vector <int> new_spectrum(n);
        for (int j = 0; j < n; j++){
            new_spectrum[j] = spectrum[(j+n-1)%n] + mass_spectrum_table[s[j]];
            ans.push_back(new_spectrum[j]);
        }
        spectrum = new_spectrum;
    }
    ans.push_back(spectrum[0] + mass_spectrum_table[s[1]]);

    sort(ans.begin(), ans.end());
    for (int x : ans) cout << x << " ";

    return 0;
}
