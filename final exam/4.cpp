#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <assert.h>
#include <set>

using namespace std;

struct trie{
    vector <map<char, int>> graph;
    vector <set<int>> colors;
    int size;
};

void add_suffix (trie & tr, string & s, int index, int color){
    int v = 0;
    tr.colors[v].insert(color);
    for (int i = index; i < s.length(); i++){
        char c = s[i];
        if (c == '#') return;
        if (tr.graph[v][c] != 0) v = tr.graph[v][c];
        else{
            v = tr.graph[v][c] = tr.size;
            tr.graph.emplace_back();
            tr.colors.emplace_back();
            tr.size++;
        }
        tr.colors[v].insert(color);
    }
}

void dfs(trie & tr, int v, string & answer, string & cur_string){
    if (tr.colors[v].size() == 1){
        if (answer.empty() || answer.size() > cur_string.size()){
            answer = cur_string;
        }
    }
    for (auto [c, u] : tr.graph[v]){
        cur_string.push_back(c);
        dfs(tr, u, answer, cur_string);
        cur_string.pop_back();
    }
}

int main() {
    freopen("../input.txt", "r", stdin);
    freopen("../output.txt", "w", stdout);

    trie tr;
    tr.graph.emplace_back();
    tr.colors.emplace_back();
    tr.size = 1;

    string text;
    int n; cin >> n;
    for (int i = 0; i < n; i++){
        string s; cin >> s;
        text += s + '#';
    }

    int color = 0;
    for (int i = 0; i < text.size(); i++){
        if (text[i] == '#') color++;
        else{
            add_suffix(tr, text, i, color);
        }
    }

    string answer;
    string cur_string;
    dfs(tr, 0, answer, cur_string);
    if (answer.empty()) cout << "doesn't exits\n";
    else cout << answer << "\n";

    return 0;
}
