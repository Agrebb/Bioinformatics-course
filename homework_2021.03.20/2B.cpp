#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <algorithm>

using namespace std;

vector <int> letters{'A', 'G', 'C', 'T'};

int main(){
    freopen("../input.txt", "r", stdin);
    freopen("../output.txt", "w", stdout);

    int k;
    cin >> k;
    string input;
    vector <string> dna;
    while (cin >> input){
        dna.push_back(input);
    }

    string ans;
    const int inf = (int)1e9;
    int min_dist = inf;
    for (int mask = 0; mask < (1 << (2*k)); mask++){
        string pattern;
        int tmp_mask = mask;
        for (int i = 0; i < k; i++){
            pattern.push_back(letters[tmp_mask & 3]);
            tmp_mask /= 4;
        }

        int dist = 0;
        for (string t : dna){
            int min_diff = inf;
            for (int i = 0; i <= t.length() - k; i++){
                int diff = 0;
                for (int j = 0; j < k; j++){
                    diff += (pattern[j] != t[i+j]);
                }
                min_diff = min(diff, min_diff);
            }
            dist += min_diff;
        }
        if (min_dist > dist){
            min_dist = dist;
            ans = pattern;
        }
    }
    cout << ans;

    return 0;
}
