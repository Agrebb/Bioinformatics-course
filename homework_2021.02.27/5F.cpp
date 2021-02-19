#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main(){
    freopen("../input.txt", "r", stdin);
    freopen("../output.txt", "w", stdout);
    //I read the table from the same input file as the two strings.
    //I removed letters from left of the table (for convenience).
    const int letters_used = 20, alphabet_size = 26;
    char letters[letters_used];
    for (int i = 0; i < letters_used; i++) cin >> letters[i];
    int matrix[alphabet_size][alphabet_size];
    for (int i = 0; i < letters_used; i++){
        for (int j = 0; j < letters_used; j++){
            cin >> matrix[letters[i] - 'A'][letters[j] - 'A'];
        }
    }
    int indel = -5;

    string s, t;
    cin >> s >> t;
    int n = s.length(), m = t.length();

    vector <vector<pair<int, int>>> dp(n+1, vector<pair<int, int>>(m+1, {0, -1}));
    int maxi = 0, maxj = 0;
    for (int i = 0; i <= n; i++){
        for (int j = 0; j <= m; j++){
            if (j > 0) {
                int value1 = dp[i][j - 1].first + indel;
                if (dp[i][j].first < value1) dp[i][j] = {value1, 1};
            }
            if (i > 0) {
                int value2 = dp[i - 1][j].first + indel;
                if (dp[i][j].first < value2) dp[i][j] = {value2, 2};
            }
            if (i > 0 && j > 0) {
                int value3 = dp[i - 1][j - 1].first + matrix[s[i - 1] - 'A'][t[j - 1] - 'A'];
                if (dp[i][j].first < value3) {
                    dp[i][j] = {value3, 3};
                }
            }
            if (dp[i][j] > dp[maxi][maxj]){
                maxi = i;
                maxj = j;
            }
        }
    }

    cout << dp[maxi][maxj].first << "\n";
    string lcs_s, lcs_t;
    int cur_i = maxi, cur_j = maxj;
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
