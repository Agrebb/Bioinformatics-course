#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

const int inf = (int)1e9;
const int letters_used = 20, alphabet_size = 26, indel = -5;
char letters[letters_used];
int matrix[alphabet_size][alphabet_size];

struct edge{
    int i1, j1, i2, j2;
};

edge get_middle_edge(string & s, string & t, int ls, int rs, int lt, int rt){
    vector <vector<pair<int, edge>>> dp(2, vector<pair<int, edge>>(rt-lt+1));
    struct edge base{-1, -1, -1, -1};
    dp[0][0] = {0, base};
    int mt = (rt - lt) / 2;
    for (int i = 0; i <= rs-ls; i++){
        for (int j = 0; j <= rt-lt; j++){
            if (i > 0 || j > 0) dp[i%2][j] = {-inf, base};
            if (j > 0) {
                int value1 = dp[i%2][j - 1].first + indel;
                if (dp[i%2][j].first < value1){
                    auto e = dp[i%2][j - 1].second;
                    if (j - 1 == mt) e.i1 = e.i2 = i, e.j1 = j-1, e.j2 = j;
                    dp[i%2][j] = {value1, e};
                }
            }
            if (i > 0) {
                int value2 = dp[(i - 1)%2][j].first + indel;
                if (dp[i%2][j].first < value2){
                    auto e = dp[(i - 1)%2][j].second;
                    if (j == mt) e.i1 = i-1, e.i2 = i, e.j1 = e.j2 = j;
                    dp[i%2][j] = {value2, e};
                }
            }
            if (i > 0 && j > 0) {
                int value3 = dp[(i - 1)%2][j - 1].first + matrix[s[i+ls-1] - 'A'][t[j+lt-1] - 'A'];
                if (dp[i%2][j].first < value3) {
                    auto e = dp[(i - 1)%2][j - 1].second;
                    if (j - 1 == mt) e.i1 = i-1, e.i2 = i, e.j1 = j-1, e.j2 = j;
                    dp[i%2][j] = {value3, e};
                }
            }
        }
    }
    auto e = dp[(rs-ls)%2][rt-lt].second;
    e.i1 += ls, e.i2 += ls, e.j1 += lt, e.j2 += lt;
    return e;
}

int main(){
    freopen("../input.txt", "r", stdin);
    freopen("../output.txt", "w", stdout);
    //I read the table from the same input file as the two strings.
    //I removed letters from left of the table (for convenience).
    for (int i = 0; i < letters_used; i++) cin >> letters[i];
    for (int i = 0; i < letters_used; i++){
        for (int j = 0; j < letters_used; j++){
            cin >> matrix[letters[i] - 'A'][letters[j] - 'A'];
        }
    }

    string s, t;
    cin >> s >> t;
    int n = s.length(), m = t.length();

    auto e = get_middle_edge(s, t, 0, n, 0, m);
    cout << "(" << e.i1 << ", " << e.j1 << ") (" << e.i2 << ", " << e.j2 << ")";

    return 0;
}
