#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

void get_cycle(string v, map<string, vector<string>> & graph, vector <string> & answer){
    for (int i = 0; i < graph[v].size(); i++){
        string u = graph[v][i];
        if (u != ""){
            graph[v][i] = "";
            get_cycle(u, graph, answer);
        }
    }
    answer.push_back(v);
}

int main(){
    freopen("../input.txt", "r", stdin);
    freopen("../output.txt", "w", stdout);
    map<string, vector<string>> graph;
    int k;
    cin >> k;
    for (int mask = 0 ; mask < (1<<k); mask++){
        string s1, s2;
        for (int i = 0; i < k - 1; i++){
            s1.push_back(((mask >> (k - i - 1)) & 1) + '0');
            s2.push_back(((mask >> (k - i - 2)) & 1) + '0');
        }
        graph[s1].push_back(s2);
    }

    vector <string> answer;
    get_cycle((graph.begin()->first), graph, answer);
    reverse(answer.begin(), answer.end());
    answer.pop_back();

    for (string s : answer){
        cout << s.back();
    }

    return 0;
}
