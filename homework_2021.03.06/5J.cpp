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
    int open = -11, ext = -1;

    string s, t;
    cin >> s >> t;
    int n = s.length(), m = t.length();

    const int inf = (int)1e9;
    vector <vector<pair<int, int>>> dp [3];
    for (int layer = 0; layer < 3; layer++) {
        dp[layer].resize(n + 1, vector<pair<int, int>>(m + 1, {-inf, -1}));
    }
    dp[2][0][0] = {0, -1};

    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            for (int l = 0; l < 3; l++){
                if (j > 0) {
                    int value1 = dp[l][i][j - 1].first + (l == 0 ? ext : open);
                    if (dp[0][i][j].first < value1) dp[0][i][j] = {value1, l};
                }
                if (i > 0) {
                    int value2 = dp[l][i - 1][j].first + (l == 1 ? ext : open);
                    if (dp[1][i][j].first < value2) dp[1][i][j] = {value2, l};
                }
                if (i > 0 && j > 0) {
                    int value3 = dp[l][i - 1][j - 1].first + matrix[s[i-1] - 'A'][t[j-1] - 'A'];
                    if (dp[2][i][j].first < value3) dp[2][i][j] = {value3, l};
                }
            }
        }
    }

    int maxl = 0;
    for (int l = 0; l < 3; l++)
        if (dp[maxl][n][m] < dp[l][n][m])
            maxl = l;
    cout << dp[maxl][n][m].first << "\n";
    string lcs_s, lcs_t;
    int cur_l = maxl, cur_i = n, cur_j = m;
    while (true){
        int new_l = dp[cur_l][cur_i][cur_j].second;
        if (new_l == -1) break;

        if (cur_l == 0){
            lcs_s.push_back('-');
            lcs_t.push_back(t[cur_j-1]);
            cur_j--;
        }
        else if (cur_l == 1){
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
        cur_l = new_l;
    }
    reverse(lcs_s.begin(), lcs_s.end());
    reverse(lcs_t.begin(), lcs_t.end());
    cout << lcs_s << "\n" << lcs_t << "\n";
    return 0;
}


