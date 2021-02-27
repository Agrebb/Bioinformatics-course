#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main(){
    freopen("../input.txt", "r", stdin);
    freopen("../output.txt", "w", stdout);

    string s, t, u;
    cin >> s >> t >> u;
    int n = s.length(), m = t.length(), k = u.length();
    const int inf = (int)1e9;
    vector<vector<vector<pair<int, int>>>> dp(n+1);
    for (int i = 0; i <= n; i++){
        dp[i].resize(m+1);
        for (int j = 0; j <= m; j++){
            dp[i][j].resize(k+1, {-inf, -1});
            for (int p = 0; p <= k; p++){
                if (i == 0 && j == 0 && p == 0) dp[i][j][p] = {0, -1};
                if (i > 0){
                    int v = dp[i-1][j][p].first;
                    if (dp[i][j][p].first < v) dp[i][j][p] = {v, 0};
                }
                if (j > 0){
                    int v = dp[i][j-1][p].first;
                    if (dp[i][j][p].first < v) dp[i][j][p] = {v, 1};
                }
                if (p > 0){
                    int v = dp[i][j][p-1].first;
                    if (dp[i][j][p].first < v) dp[i][j][p] = {v, 2};
                }
                if (i > 0 && j > 0 && p > 0 && s[i-1] == t[j-1] && t[j-1] == u[p-1]){
                    int v = dp[i-1][j-1][p-1].first + 1;
                    if (dp[i][j][p].first < v) dp[i][j][p] = {v, 3};
                }
            }
        }
    }

    cout << dp[n][m][k].first << "\n";
    string lcs_s, lcs_t, lcs_u;
    int cur_i = n, cur_j = m, cur_p = k;
    while (true){
        int type = dp[cur_i][cur_j][cur_p].second;
        if (type == -1) break;

        char next_s, next_t, next_u;
        if (type == 0){
            cur_i--;
            next_s = s[cur_i], next_t = next_u = '-';
        }
        else if (type == 1){
            cur_j--;
            next_t = t[cur_j], next_s = next_u = '-';
        }
        else if (type == 2){
            cur_p--;
            next_u = u[cur_p], next_s = next_t = '-';
        }
        else{
            cur_i--; cur_j--; cur_p--;
            next_s = s[cur_i], next_t = t[cur_j], next_u = u[cur_p];
        }
        lcs_s.push_back(next_s);
        lcs_t.push_back(next_t);
        lcs_u.push_back(next_u);
    }
    reverse(lcs_s.begin(), lcs_s.end());
    reverse(lcs_t.begin(), lcs_t.end());
    reverse(lcs_u.begin(), lcs_u.end());
    cout << lcs_s << "\n" << lcs_t << "\n" << lcs_u << "\n";

    return 0;
}
