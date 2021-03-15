#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <algorithm>

using namespace std;

vector <int> letters{'A', 'G', 'C', 'T'};

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

int main(){
    freopen("../input.txt", "r", stdin);
    freopen("../output.txt", "w", stdout);

    int k, d;
    cin >> k >> d;
    string input;
    vector <string> dna;
    while (cin >> input){
        dna.push_back(input);
    }
    set <string> ans;
    for (string s : dna){
        for (int i = 0; i <= s.length() - k; i++){
            string kmer;
            for (int j = 0; j < k; j++) kmer.push_back(s[i+j]);
            auto neighbours = get_neighbours(kmer, d);

            for (string pattern : neighbours) {
                bool to_ans = true;
                for (string t : dna) {
                    bool ok = false;
                    for (int p = 0; p <= t.length() - k; p++) {
                        int diff = 0;
                        for (int j = 0; j < k; j++) {
                            diff += (t[p + j] != pattern[j]);
                        }
                        if (diff <= d) {
                            ok = true;
                            break;
                        }
                    }
                    if (!ok) {
                        to_ans = false;
                        break;
                    }
                }
                if (to_ans) ans.insert(pattern);
            }
        }
    }
    for (string s : ans) cout << s << " ";

    return 0;
}
