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

void add_string (trie & tr, string & s){
    int v = 0;
    for (char c : s){
        if (tr.graph[v][c] != 0) v = tr.graph[v][c];
        else{
            v = tr.graph[v][c] = tr.size;
            tr.graph.emplace_back();
            tr.size++;
        }
    }
}

int main() {
    freopen("../input.txt", "r", stdin);
    freopen("../output.txt", "w", stdout);

    trie tr;
    tr.graph.emplace_back();
    tr.size = 1;

    string s;
    while (cin >> s){
        add_string(tr, s);
    }

    for (int v = 0; v < tr.size; v++){
        for (auto [c, u] : tr.graph[v]){
            cout << v << "->" << u << ":" << c << "\n";
        }
    }

    return 0;
}
