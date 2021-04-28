#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <assert.h>

using namespace std;

struct trie{
    vector <map<char, int>> graph;
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
            tr.size++;
        }
    }
}

void dfs(trie & tr, int v){
    bool split = (tr.graph[v].size() != 1);
    if (split && v != 0) cout << "\n";
    for (auto [c, u] : tr.graph[v]){
        cout << c;
        dfs(tr, u);
    }
}

int main() {
    freopen("../input.txt", "r", stdin);
    freopen("../output.txt", "w", stdout);

    trie tr;
    tr.graph.emplace_back();
    tr.size = 1;

    string text;
    cin >> text;
    for (int index = 0; index < text.length(); index++)
        add_suffix(tr, text, index);

    dfs(tr, 0);

    return 0;
}
