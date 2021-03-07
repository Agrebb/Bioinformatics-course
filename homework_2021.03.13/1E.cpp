#include <iostream>
#include <string>
#include <map>
#include <set>
#include <algorithm>

using namespace std;

int main(){
    freopen("../input.txt", "r", stdin);
    freopen("../output.txt", "w", stdout);

    string s;
    cin >> s;
    int k, l, t;
    cin >> k >> l >> t;
    map <string, int> freq;
    set <string> clumps;
    for (int i = 0; i <= l - k; i++){
        string t0;
        for (int j = 0; j < k; j++){
            t0.push_back(s[i+j]);
        }
        freq[t0]++;
        if (freq[t0] >= t) clumps.insert(t0);
    }
    for (int i = 0; i < s.length() - l; i++){
        string t1, t2;
        for (int j = 0; j < k; j++){
            t1.push_back(s[i+j]);
            t2.push_back(s[i+j+l-k+1]);
        }
        freq[t1]--;
        freq[t2]++;
        if (freq[t2] >= t) clumps.insert(t2);
    }
    for (string clump : clumps) cout << clump << " ";

    return 0;
}
