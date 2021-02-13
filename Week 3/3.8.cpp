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
    string s;
    while (cin >> s){
        string s1, s2;
        for (int i = 0; i < k - 1; i++){
            s1.push_back(s[i]);
            s2.push_back(s[i+1]);
        }
        graph[s1].push_back(s2);

        graph[s2] = graph[s2]; // we want add s2 to map if it wasn't there, and not to change anything otherwise
    }

    map<string, int> balance;
    for (auto vertex : graph){
        for (string neighbour : vertex.second){
            balance[vertex.first]++;
            balance[neighbour]--;
        }
    }
    string head = "", tail = "";
    for (auto vertex : graph){
        string v = vertex.first;
        if (balance[v] < 0) head = v;
        if (balance[v] > 0) tail = v;
    }
    if (head != "" && tail != "") graph[head].push_back(tail);

    vector <string> answer;
    get_cycle((graph.begin()->first), graph, answer);
    reverse(answer.begin(), answer.end());
    answer.pop_back();

    int start_index = 0;
    for (int i = 0; i < answer.size(); i++){
        if (answer[i] == head && answer[(i+1) % answer.size()] == tail)
            start_index = i+1;
    }
    for (int i = 0; i < answer.size(); i++){
        if (i == 0) cout << answer[(i + start_index) % answer.size()];
        else cout << answer[(i + start_index) % answer.size()].back();
    }

    return 0;
}
