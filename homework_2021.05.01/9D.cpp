#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <assert.h>

using namespace std;

struct trie{
    vector <map<char, int>> graph;
    vector <int> cnt;
    int size;
};

void add_suffix (trie & tr, string & s, int index, pair<int, int> & answer){
    int v = 0;
    for (int i = index; i < s.length(); i++){
        char c = s[i];
        if (tr.graph[v][c] != 0) v = tr.graph[v][c];
        else{
            v = tr.graph[v][c] = tr.size;
            tr.graph.emplace_back();
            tr.cnt.emplace_back(0);
            tr.size++;
        }
        tr.cnt[v]++;
        if (tr.cnt[v] == 2){
            if (answer.second - answer.first < i - index){
                answer = {index, i};
            }
        }
    }
}

int main() {
    freopen("../input.txt", "r", stdin);
    freopen("../output.txt", "w", stdout);

    trie tr;
    tr.graph.emplace_back();
    tr.cnt.emplace_back(0);
    tr.size = 1;

    string text;
    cin >> text;
    pair<int, int> answer = {0, 0};
    for (int index = 0; index < text.length(); index++)
        add_suffix(tr, text, index, answer);

    for (int i = answer.first; i <= answer.second; i++)
        cout << text[i];

    return 0;
}
