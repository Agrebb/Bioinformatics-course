#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main(){
    freopen("../input.txt", "r", stdin);
    freopen("../output.txt", "w", stdout);

    string s, t;
    int d;
    cin >> t >> s >> d;
    vector <int> ans;
    for (int i = 0; i <= s.length() - t.length(); i++){
        int cnt = 0;
        for (int j = 0; j < t.length(); j++){
            cnt += s[i+j] != t[j];
        }
        if (cnt <= d) ans.push_back(i);
    }
    for (int index : ans) cout << index << " ";

    return 0;
}
