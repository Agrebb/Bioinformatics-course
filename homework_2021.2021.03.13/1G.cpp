#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main(){
    freopen("../input.txt", "r", stdin);
    freopen("../output.txt", "w", stdout);

    string s, t;
    cin >> s >> t;
    int ans = 0;
    for (int i = 0; i < s.length(); i++) ans += s[i] != t[i];
    cout << ans;

    return 0;
}
