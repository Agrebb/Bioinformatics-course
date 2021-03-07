#include <iostream>
#include <string>
#include <map>
#include <algorithm>

using namespace std;

int main(){
    freopen("../input.txt", "r", stdin);
    freopen("../output.txt", "w", stdout);

    string s;
    cin >> s;
    int k;
    cin >> k;
    map <string, int> freq;
    int maxfreq = 0;
    for (int i = 0; i < s.length() - k; i++){
        string t;
        for (int j = i; j < i + k; j++){
            t.push_back(s[j]);
        }
        freq[t]++;
        maxfreq = max(maxfreq, freq[t]);
    }
    for (auto kmer : freq){
        if (kmer.second == maxfreq) cout << kmer.first << " ";
    }
    return 0;
}

