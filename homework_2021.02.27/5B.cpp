#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main(){
    freopen("../input.txt", "r", stdin);
    freopen("../output.txt", "w", stdout);
    int n, m;
    cin >> n >> m;
    vector <vector <int>> down(n), right(n+1);
    for (int i = 0; i < n; i++){
        down[i].resize(m+1);
        for (int j = 0; j < m+1; j++) cin >> down[i][j];
    }
    string divide; cin >> divide;
    for (int i = 0; i < n+1; i++){
        right[i].resize(m);
        for (int j = 0; j < m; j++) cin >> right[i][j];
    }

    vector <vector<int>> dp(n+1);
    for (int i = 0; i < n+1; i++){
        dp[i].resize(m+1, 0);
        for (int j = 0; j < m+1; j++){
            if (i > 0) dp[i][j] = max(dp[i][j], dp[i-1][j] + down[i-1][j]);
            if (j > 0) dp[i][j] = max(dp[i][j], dp[i][j-1] + right[i][j-1]);
        }
    }
    cout << dp[n][m] << "\n";
    return 0;
}
