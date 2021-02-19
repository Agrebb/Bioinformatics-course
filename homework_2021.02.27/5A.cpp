#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

vector <int> parse_string (string s){
    vector <int> result;
    int cur = 0;
    bool isnumber = false;
    for (int i = 0; i < s.length(); i++){
        if (s[i] >= '0' && s[i] <= '9'){
            cur *= 10;
            cur += s[i] - '0';
            isnumber = true;
        }
        else if (isnumber){
            result.push_back(cur);
            isnumber = false;
            cur = 0;
        }
    }
    if (isnumber) result.push_back(cur);
    return result;
}

int main(){
    freopen("../input.txt", "r", stdin);
    freopen("../output.txt", "w", stdout);
    int n;
    cin >> n;
    string s;
    cin >> s;
    auto coins = parse_string(s);

    const int inf = (int)1e9;
    vector <int> dp(n+1, inf);
    dp[0] = 0;
    for (int i = 1; i <= n; i++){
        for (auto coin : coins){
            if (i >= coin) dp[i] = min(dp[i], dp[i - coin] + 1);
        }
    }
    cout << dp[n] << "\n";

    return 0;
}
