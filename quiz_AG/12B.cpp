#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <set>

using namespace std;

map<char, int> phi{{'A', 0}, {'C', 1}, {'G', 2}, {'T', 3}};
map<char, int> inverse_phi{{'A', 3}, {'C', 2}, {'G', 1}, {'T', 0}};
map<char, char> invert{{'A', 'T'}, {'T', 'A'}, {'C', 'G'}, {'G', 'C'}};
const long long inf = (long long)1e18;

vector <pair<int, int>> get_minimizers(string s, int w, int k){
    vector <pair<int, int>> ans;
    int n = s.length();
    for (int i = 0; i <= n - w - k + 1; i++){
        long long hsh = 0, hsh_reversed = 0, largest_power = 1;
        for (int j = 0; j < k; j++){
            hsh *= 4;
            largest_power *= 4;
            hsh_reversed *= 4;
            hsh += phi[s[i+j]];
            hsh_reversed += inverse_phi[s[i+k-j-1]];
        }
        largest_power /= 4;

        bool equal = hsh == hsh_reversed;
        long long min_hash = equal ? inf : hsh, min_hash_reversed = equal ? inf : hsh_reversed;
        int index = i, index_reversed = i+k-1;
        for (int j = 0; j < w - 1; j++){
            hsh -= phi[s[i+j]] * largest_power;
            hsh_reversed -= inverse_phi[s[i+j]];
            hsh *= 4;
            hsh_reversed /= 4;
            hsh += phi[s[i+j+k]];
            hsh_reversed += inverse_phi[s[i+j+k]] * largest_power;

            if (hsh == hsh_reversed) continue;
            if (min_hash > hsh){
                min_hash = hsh;
                index = i+j+1;
            }
            if (min_hash_reversed > hsh_reversed){
                min_hash_reversed = hsh_reversed;
                index_reversed = i+j+k;
            }
        }
        if (min_hash < min_hash_reversed) ans.push_back({index, 1});
        else if (min_hash_reversed != inf) ans.push_back({index_reversed, -1});
    }
    return ans;
}

int main() {
    int w, k; cin >> w >> k;
    string s; cin >> s;
    auto ans = get_minimizers(s, w, k);

    set <string> minimizers;
    for (auto p : ans){
        int index = p.first, reversed = p.second;
        string new_minimizer;
        for (int j = index; j != index + k*reversed; j += reversed)
            new_minimizer.push_back(reversed == 1 ? s[j] : invert[s[j]]);
        minimizers.insert(new_minimizer);
    }
    for (auto x : minimizers) cout << x << " ";

    return 0;
}
