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

    string text;
    cin >> text;

    string s;
    while (cin >> s){
        add_string(tr, s);
    }

    for (int i = 0; i < text.length(); i++){
        int v = 0;
        for (int j = 0;;j++){
            if (tr.graph[v].size() == 0){
                cout << i << " ";
                break;
            }
            if (tr.graph[v][text[i+j]] != 0){
                v = tr.graph[v][text[i+j]];
            }
            else break;
        }
    }

    return 0;
}
