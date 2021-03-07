#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <algorithm>

using namespace std;

vector <int> letters{'A', 'G', 'C', 'T'};
map <char, char> inverse{{'A', 'T'}, {'T', 'A'}, {'G', 'C'}, {'C', 'G'}};

set <string> get_neighbours(string s, int d){
    set <string> res;
    int k = s.length();
    vector <int> choice(k, 0);
    for (int i = 0; i < d; i++) choice[i] = 1;
    while (true){
        for (int mask = 0; mask < (1 << (2*d)); mask++){
            string t = s;
            int tmp_mask = mask;
            for (int i = 0; i < k; i++){
                if (choice[i]){
                    t[i] = letters[tmp_mask & 3];
                    tmp_mask /= 4;
                }
            }
            res.insert(t);
        }

        next_permutation(choice.begin(), choice.end());
        int finish = 1;
        for (int i = 0; i < d; i++) finish &= choice[i];
        if (finish) break;
    }
    return res;
}

void update_freqs(string s, int k, int d, map <string, int> & freq){
    for (int i = 0; i <= s.length() - k; i++){
        string t;
        for (int j = 0; j < k; j++) t.push_back(s[i+j]);
        auto neighbours = get_neighbours(t, d);
        for (string neighbour : neighbours){
            freq[neighbour]++;
        }
    }
}

int main(){
    freopen("../input.txt", "r", stdin);
    freopen("../output.txt", "w", stdout);

    string s;
    cin >> s;
    int k, d; cin >> k >> d;

    map<string, int> freq;
    update_freqs(s, k, d, freq);

    int max_freq = -1;
    for (auto kmer : freq){
        max_freq = max(max_freq, kmer.second);
    }
    for (auto kmer : freq){
        if (kmer.second == max_freq) cout << kmer.first << " ";
    }

    return 0;
}
