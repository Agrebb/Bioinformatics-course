#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <assert.h>

using namespace std;

const int maxn = 10000;

void add_to_graph(vector <vector<pair<int, int>>> & gr, vector <pair<int, int>> & cycle,
        int & num, int color){
    int flag = cycle[0].second;
    for (int i = 0; i < cycle.size(); i++){
        int j = (i+1) % cycle.size();
        int newflag = flag ^ (cycle[i].second != cycle[j].second);

        int v1 = cycle[i].first + maxn * flag, v2 = cycle[j].first + maxn * (newflag ^ 1);
        gr[v1].push_back({v2, color});
        gr[v2].push_back({v1, color});
        flag = newflag;
        num++;
    }
}

void parse_string (vector <vector<pair<int, int>>> & gr, string s, int & num, int color){
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
            add_to_graph(gr, cycle, num, color);
            cycle.clear();
        }
    }
}

void dfs(vector <vector<pair<int, int>>> & gr, vector <int> & used,
        vector <pair<int, int>> & red_edges, int v){
    if (used[v]) return;
    used[v] = 1;
    for (auto [u, color] : gr[v]){
        if (!used[u] && color == 1) red_edges.push_back({v, u});
        dfs(gr, used, red_edges, u);
    }
}

void red_dfs(vector <vector<pair<int, int>>> & gr, vector <int> & used,
         vector <int> & result, int v){
    if (used[v]) return;
    result.push_back(v);
    int vv = (v > maxn) ? v - maxn : v + maxn;
    used[v] = used[vv] = 1;
    for (auto [u, color] : gr[v]){
        if (color == 1) {
            if (u > maxn) u -= maxn;
            else u += maxn;
            red_dfs(gr, used, result, u);
        }
    }
}

string recover_string(vector <vector <pair<int, int>>> gr, int n){
    vector <int> used(2*maxn, 0);
    vector <int> result;
    string s;
    for (int comp = 0; comp <= 1; comp++) {
        for (int i = 1; i <= n; i++) {
            int v = i + comp * maxn;
            if (!used[v]) {
                red_dfs(gr, used, result, v);

                s += "(";
                for (int j = 0; j < result.size(); j++) {
                    if (j > 0) s += " ";
                    if (result[j] > maxn) result[j] = - (result[j] - maxn);
                    if (result[j] > 0) s += "+";
                    s += to_string(result[j]);
                }
                s += ")";
                result.clear();
            }
        }
    }
    return s;
}

int main() {
    freopen("../input.txt", "r", stdin);
    freopen("../output.txt", "w", stdout);

    vector <vector <pair<int, int>>> graph(2*maxn);

    string s, t; getline(cin, s); getline(cin, t);
    cout << s << "\n";
    while (true) {
        int ns = 0, nt = 0;
        parse_string(graph, s, ns, 1);
        parse_string(graph, t, nt, 2);
        assert(ns == nt);

        vector <int> used(2*maxn, 0);
        bool finish = true;
        for (int comp = 0; comp <= 1; comp++) {
            for (int i = 1; i <= ns; i++) {
                int v = i + comp * maxn;
                if (!used[v]) {
                    vector<pair<int, int>> red_edges;
                    dfs(graph, used, red_edges, v);
                    if (red_edges.size() > 1) {
                        int v0 = red_edges[0].first, u0 = red_edges[0].second;
                        int v1 = red_edges[1].first, u1 = red_edges[1].second;
                        for (auto &p : graph[v0]) {
                            if (p.first == u0) p = {u1, 1};
                        }
                        for (auto &p : graph[v1]) {
                            if (p.first == u1) p = {u0, 1};
                        }
                        for (auto &p : graph[u0]) {
                            if (p.first == v0) p = {v1, 1};
                        }
                        for (auto &p : graph[u1]) {
                            if (p.first == v1) p = {v0, 1};
                        }

                        s = recover_string(graph, ns);
                        cout << s << "\n";
                        finish = false;
                        break;
                    }
                }
            }
        }
        if (finish) break;
    }

    return 0;
}
