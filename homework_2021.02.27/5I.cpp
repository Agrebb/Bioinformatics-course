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
    vector <vector<pair<int, int>>> dp(n+1, vector<pair<int, int>>(m+1, {-inf, -1}));
    dp[0][0] = {0, -1};
    int maxj = 0;
    for (int i = 0; i <= n; i++){
        for (int j = 0; j <= m; j++){
            if (i > 0) dp[i][j] = dp[0][j];

            if (j > 0) {
                int value1 = dp[i][j - 1].first - 2;
                if (dp[i][j].first < value1) dp[i][j] = {value1, 1};
            }
            if (i > 0) {
                int value2 = dp[i - 1][j].first - 2;
                if (dp[i][j].first < value2) dp[i][j] = {value2, 2};
            }
            if (i > 0 && j > 0) {
                int value3 = dp[i - 1][j - 1].first + (s[i-1] == t[j-1] ? 1 : -2);
                if (dp[i][j].first < value3) {
                    dp[i][j] = {value3, 3};
                }
            }
            if (i == n && dp[i][j] > dp[i][maxj]){
                maxj = j;
            }
        }
    }

    cout << dp[n][maxj].first << "\n";
    string lcs_s, lcs_t;
    int cur_i = n, cur_j = maxj;
    while (true){
        int type = dp[cur_i][cur_j].second;
        if (type == -1) break;

        if (type == 1){
            lcs_s.push_back('-');
            lcs_t.push_back(t[cur_j-1]);
            cur_j--;
        }
        else if (type == 2){
            lcs_s.push_back(s[cur_i-1]);
            lcs_t.push_back('-');
            cur_i--;
        }
        else{
            lcs_s.push_back(s[cur_i-1]);
            lcs_t.push_back(t[cur_j-1]);
            cur_i--;
            cur_j--;
        }
    }
    reverse(lcs_s.begin(), lcs_s.end());
    reverse(lcs_t.begin(), lcs_t.end());
    cout << lcs_s << "\n" << lcs_t << "\n";
    return 0;
}
