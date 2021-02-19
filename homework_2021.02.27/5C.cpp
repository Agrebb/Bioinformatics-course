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
    vector <vector<pair<int, int>>> dp(n+1, vector<pair<int, int>>(m+1));
    for (int i = 1; i <= n; i++){
        for (int j = 1; j <= m; j++){
            if (dp[i-1][j].first < dp[i][j-1].first) dp[i][j] = {dp[i][j-1].first, 1};
            else dp[i][j] = {dp[i-1][j].first, 2};

            if (s[i-1] == t[j-1] && dp[i][j].first < dp[i-1][j-1].first + 1){
                dp[i][j] = {dp[i-1][j-1].first + 1, 3};
            }
        }
    }
    string lcs;
    int cur_i = n, cur_j = m;
    while (dp[cur_i][cur_j].first > 0){
        int type = dp[cur_i][cur_j].second;

        if (type == 1) cur_j--;
        else if (type == 2) cur_i--;
        else{
            lcs.push_back(s[cur_i-1]);
            cur_i--;
            cur_j--;
        }
    }
    reverse(lcs.begin(), lcs.end());
    cout << lcs << "\n";
    return 0;
}
