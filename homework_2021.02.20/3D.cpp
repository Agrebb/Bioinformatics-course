#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

int main(){
    freopen("../input.txt", "r", stdin);
    freopen("../output.txt", "w", stdout);
    map <string, vector<string>> graph;
    int k;
    cin >> k;
    string text;
    cin >> text;
    for (int i = 0; i < text.size() - k + 1; i++){
        string s, t;
        for (int j = 0; j < k - 1; j++){
            s.push_back(text[i+j]);
            t.push_back(text[i+j+1]);
        }
        graph[s].push_back(t);
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
