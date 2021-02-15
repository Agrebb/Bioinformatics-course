#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

int main(){
    freopen("../input.txt", "r", stdin);
    freopen("../output.txt", "w", stdout);
    map<string, vector<string>> graph;
    map <string, int> in, out;
    string s;
    while (cin >> s){
        string s1, s2;
        for (int i = 0; i+1 < s.size(); i++) {
            s1.push_back(s[i]);
            s2.push_back(s[i+1]);
        }
        graph[s1].push_back(s2);
        out[s1]++; in[s2]++;

        graph[s2] = graph[s2]; // we want add s2 to map if it wasn't there, and not to change anything otherwise
    }

    vector <string> paths;
    for (auto vertex : graph){
        string v = vertex.first;
        if (out[v] != 1 || in[v] != 1){
            for (int i = 0; i < vertex.second.size(); i++){
                string u = vertex.second[i];
                if (u == "") continue;

                string path = v + u.back();
                graph[v][i] = "";
                while (out[u] == 1 && in[u] == 1){
                    string next_u = graph[u][0];
                    if (next_u == "") break;
                    graph[u][0] = "";
                    u = next_u;
                    path.push_back(u.back());
                }
                paths.push_back(path);
            }
        }
    }
    sort(paths.begin(), paths.end());

    for (string path : paths) cout << path << "\n";

    return 0;
}
