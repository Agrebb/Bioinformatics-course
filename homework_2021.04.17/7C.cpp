#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <assert.h>

using namespace std;

bool get_path(vector <vector<pair<int, int>>> & tree, int v, int parent,
        const int end, vector <int> & path){
    if (v == end){
        path.push_back(v);
        return true;
    }
    bool result = false;
    for (auto [u, w] : tree[v]){
        if (u != parent){
            result |= get_path(tree, u, v, end, path);
        }
    }
    if (result) path.push_back(v);
    return result;
}

void solve (vector <vector<int>> & d, int left, vector <vector<pair<int, int>>> & tree){
    if (left == 2){
        tree[0].push_back({1, d[0][1]});
        tree[1].push_back({0, d[0][1]});
        return;
    }
    solve(d, left - 1, tree);

    int i = left - 1, j = 0, k = 1;
    for (int curk = 2; curk < i; curk++){
        if (d[i][j] + d[i][k] - d[j][k] > d[i][j] + d[i][curk] - d[j][curk]) k = curk;
    }
    int limb = (d[i][j] + d[i][k] - d[j][k]) / 2;
    vector <int> path;
    get_path(tree, j, -1, k, path);
    reverse(path.begin(), path.end());

    int cur_length = 0;
    for (int index = 0; index < path.size(); index++){
        int v1 = path[index], v2 = path[index + 1];

        int new_length = cur_length;
        for (auto [u, w] : tree[v1]){
            if (u == v2) new_length += w;
        }
        if (new_length == d[i][j] - limb){
            tree[v2].push_back({i, limb});
            tree[i].push_back({v2, limb});
            break;
        }
        else if (new_length > d[i][j] - limb){
            int new_node = tree.size();
            tree.push_back(vector <pair<int, int>>());
            for (auto &p : tree[v1]){
                if (p.first == v2){
                    p.first = new_node;
                    p.second = (d[i][j] - limb) - cur_length;
                    tree[new_node].push_back({v1, p.second});
                }
            }
            for (auto &p : tree[v2]){
                if (p.first == v1){
                    p.first = new_node;
                    p.second = new_length - (d[i][j] - limb);
                    tree[new_node].push_back({v2, p.second});
                }
            }
            tree[new_node].push_back({i, limb});
            tree[i].push_back({new_node, limb});
            break;
        }
        cur_length = new_length;
    }
}

int main() {
    freopen("../input.txt", "r", stdin);
    freopen("../output.txt", "w", stdout);

    int n; cin >> n;
    vector <vector <int>> d(n, vector <int>(n));
    for (int i = 0; i < n; i++){
        for (int k = 0; k < n; k++){
            cin >> d[i][k];
        }
    }
    vector <vector<pair<int, int>>> tree(n);
    solve(d, n, tree);
    for (int v = 0; v < tree.size(); v++){
        for (auto [u, w] : tree[v]){
            cout << v << "->" << u << ":" << w << endl;
        }
    }

    return 0;
}
