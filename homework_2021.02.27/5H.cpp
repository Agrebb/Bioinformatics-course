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
    int n = s.length(), m = t.length();

    const int inf = (int)1e9;
    vector <vector<int>> dp(n+1, vector<int>(m+1, inf));
    dp[0][0] = 0;
    for (int i = 0; i <= n; i++){
        for (int j = 0; j <= m; j++){
            if (j > 0) dp[i][j] = min(dp[i][j], dp[i][j-1] + 1);
            if (i > 0) dp[i][j] = min(dp[i][j], dp[i-1][j] + 1);
            if (i > 0 && j > 0) dp[i][j] = min(dp[i][j], dp[i-1][j-1] + (s[i-1] != t[j-1]));
        }
    }
    cout << dp[n][m] << "\n";

    return 0;
}
