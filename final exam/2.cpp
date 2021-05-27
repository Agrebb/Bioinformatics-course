#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <assert.h>

using namespace std;

const int letters_used = 20, alphabet_size = 26;
char letters[letters_used];
int matrix[alphabet_size][alphabet_size];

vector <vector<int>> graph;
vector <vector<int>> dp;
vector <string> labels;

void dfs(int v, int index){
    int cnt = 0;
    for (auto u : graph[v]){
        dfs(u, index);
        cnt++;
    }
    if (cnt == 0){
        int letter_index = -1;
        for (int i = 0; i < letters_used; i++){
            if (letters[i] = labels[v][index]) letter_index = i;
        }
        dp[v][letter_index] = 0;
    }
    else{
        for (auto u : graph[v]){
            for (int l1 = 0; l1 < letters_used; l1++){
                int maxval = 0;
                for (int l2 = 0; l2 < letters_used; l2++){
                    maxval = max(maxval, matrix[l1][l2] + dp[u][l2]);
                }
                dp[v][l1] += maxval;
            }
        }
    }
}

int main() {
    freopen("../input.txt", "r", stdin);
    freopen("../output.txt", "w", stdout);
    //I read the table from the same input file as the two strings.
    //I removed letters from left of the table (for convenience).
    for (int i = 0; i < letters_used; i++) cin >> letters[i];
    for (int i = 0; i < letters_used; i++){
        for (int j = 0; j < letters_used; j++){
            cin >> matrix[i][j];
        }
    }

    // don't have time to adjust input format, sorry)

    int n, leaves; cin >> n >> leaves;
    int root = n;
    graph.resize(n);
    for (int i = 0; i < n - 1; i++){
        int u, v; cin >> u >> v;
        graph[u].push_back(v);
    }
    labels.resize(leaves);
    for (int i = 0; i < leaves; i++){
        cin >> labels[i];
    }

    dp.resize(n);
    for (int i = 0; i < n; i++) dp[i].resize(letters_used);

    int m = labels[0].length();
    const int inf = 1e9;
    for (int index = 0; index < m; index++){
        for (int i = 0; i < n; i++){
            for (int l = 0; l < letters_used; l++) dp[i][l] = -inf;
        }
        dfs(root, index);
    }

    int ans = -inf;
    for (int l = 0; l < letters_used; l++){
        int ans_l = 0;
        for (int index = 0; index < m; index++){
            ans_l += dp[root][l];
        }
        ans = max(ans, ans_l);
    }
    cout << ans;


    return 0;
}

