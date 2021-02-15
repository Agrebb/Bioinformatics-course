#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

int main(){
    freopen("../input.txt", "r", stdin);
    freopen("../output.txt", "w", stdout);
    map <string, vector<string>> graph;
    string s;
    while (cin >> s){
        string s1, s2;
        for (int i = 0; i + 1 < s.size(); i++){
            s1.push_back(s[i]);
            s2.push_back(s[i+1]);
        }
        graph[s1].push_back(s2);
    }
    for (auto vertex : graph){
        if (!vertex.second.empty()){
            cout << vertex.first << " -> ";
            for (int i = 0; i < vertex.second.size(); i++){
                if (i > 0) cout << ",";
                cout << vertex.second[i];
            }
            cout << "\n";
        }
    }

    return 0;
}
