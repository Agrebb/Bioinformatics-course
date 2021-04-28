#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <assert.h>

using namespace std;

struct trie{
    vector <map<char, int>> graph;
    vector <int> position;
    int size;
};

void add_suffix (trie & tr, string & s, int index){
    int v = 0;
    for (int i = index; i < s.length(); i++){
        char c = s[i];
        if (tr.graph[v][c] != 0) v = tr.graph[v][c];
        else{
            v = tr.graph[v][c] = tr.size;
            tr.graph.emplace_back();
            tr.position.emplace_back(-1);
            tr.size++;
        }
        if (i == s.length() - 1){
            tr.position[v] = index;
        }
    }
}

void dfs(trie & tr, int v, vector <int> & answer){
    if (tr.position[v] != -1) answer.push_back(tr.position[v]);
    for (auto [c, u] : tr.graph[v]){
        dfs(tr, u, answer);
    }
}

int main() {
    freopen("../input.txt", "r", stdin);
    freopen("../output.txt", "w", stdout);

    trie tr;
    tr.graph.emplace_back();
    tr.position.emplace_back(-1);
    tr.size = 1;

    string text;
    cin >> text;
    for (int index = 0; index < text.length(); index++)
        add_suffix(tr, text, index);

    vector <int> answer;
    dfs(tr, 0, answer);
    for (int i = 0; i < answer.size(); i++){
        if (i > 0) cout << ", ";
        cout << answer[i];
    }

    return 0;
}
