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
    int start, finish;
    cin >> start >> finish;
    string s;
    vector<vector<pair<int, int>>> gr;
    while (cin >> s){
        auto edge = parse_string(s);
        while (gr.size() <= max(edge[0], edge[1])) gr.push_back(vector <pair<int, int>>());
        gr[edge[0]].push_back({edge[1], edge[2]});
    }

    const int inf = (int)1e9;
    vector <pair<int, int>> dp(gr.size(), {-inf, -1});
    dp[start] = {0, -1};

    for (int v = 0; v < gr.size(); v++){
        for (auto edge : gr[v]){
            if (dp[edge.first].first < dp[v].first + edge.second){
                dp[edge.first] = {dp[v].first + edge.second, v};
            }
        }
    }
    cout << dp[finish].first << "\n";

    vector <int> answer;
    int curv = finish;
    while (curv != -1){
        answer.push_back(curv);
        curv = dp[curv].second;
    }
    reverse(answer.begin(), answer.end());
    for (int i = 0; i < answer.size(); i++){
        if (i > 0) cout << "->";
        cout << answer[i];
    }

    return 0;
}
