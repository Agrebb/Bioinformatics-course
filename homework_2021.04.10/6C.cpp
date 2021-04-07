#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <assert.h>

using namespace std;

const int maxn = 10000;

void add_to_graph(vector <vector<int>> & gr, vector <pair<int, int>> & cycle, int & num){
    int flag = cycle[0].second;
    for (int i = 0; i < cycle.size(); i++){
        int j = (i+1) % cycle.size();
        int newflag = flag ^ (cycle[i].second != cycle[j].second);

        int v1 = cycle[i].first + maxn * flag, v2 = cycle[j].first + maxn * (newflag ^ 1);
        gr[v1].push_back(v2);
        gr[v2].push_back(v1);
        flag = newflag;
        num++;
    }
}

void parse_string (vector <vector<int>> & gr, string s, int & num){
    vector <pair<int, int>> cycle;
    int cur = 0, sgn = 0;
    for (char c : s){
        if (c >= '0' && c <= '9'){
            cur = (cur * 10) + c - '0';
        }
        else if (c == '-') sgn = 1;
        else{
            if (cur > 0){
                cycle.push_back({cur, sgn});
                cur = sgn = 0;
            }
        }
        if (c == ')'){
            add_to_graph(gr, cycle, num);
            cycle.clear();
        }
    }
}

void dfs(vector <vector<int>> & gr, vector <int> & used, int v){
    if (used[v]) return;
    used[v] = 1;
    for (int u : gr[v]){
        dfs(gr, used, u);
    }
}

int main() {
    freopen("../input.txt", "r", stdin);
    freopen("../output.txt", "w", stdout);

    vector <vector <int>> graph(2*maxn);

    string s, t; getline(cin, s); getline(cin, t);
    int ns = 0, nt = 0;
    parse_string(graph, s, ns);
    parse_string(graph, t, nt);
    assert(ns == nt);

    vector <int> used(2*maxn, 0);
    int num_cycles = 0;
    for (int comp = 0; comp <= 1; comp++) {
        for (int i = 1; i <= ns; i++) {
            int v = i + maxn * comp;
            if (!used[v]) {
                num_cycles++;
                dfs(graph, used, v);
            }
        }
    }
    cout << ns - num_cycles << "\n";

    return 0;
}
