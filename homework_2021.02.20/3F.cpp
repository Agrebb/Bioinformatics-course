#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

void get_cycle(int v, vector <vector<int>> & graph, vector <int> & answer){
    for (int i = 0; i < graph[v].size(); i++){
        int u = graph[v][i];
        if (u != -1){
            graph[v][i] = -1;
            get_cycle(u, graph, answer);
        }
    }
    answer.push_back(v);
}

vector <int> parse_string (string s){
    vector <int> result;
    int cur = 0;
    bool isnumber = false;
    for (int i = 0; i < s.length(); i++){
        if (s[i] >= '0' && s[i] <= '9'){
            cur *= 10;
            cur += s[i] - '0';
            isnumber = true;
        }
        else if (isnumber){
            result.push_back(cur);
            isnumber = false;
            cur = 0;
        }
    }
    if (isnumber) result.push_back(cur);
    return result;
}

vector<vector<int>> read_graph(){
    vector <vector <int>> input;
    int max_vertex = 0;
    string s;
    while (getline(cin, s)){
        input.push_back(parse_string(s));
        max_vertex = max(max_vertex, input.back()[0]);
    }
    vector <vector<int>> graph(max_vertex + 1);
    for (auto line : input){
        for (int i = 1; i < line.size(); i++) graph[line[0]].push_back(line[i]);
    }
    return graph;
}

int main(){
    freopen("../input.txt", "r", stdin);
    freopen("../output.txt", "w", stdout);
    auto graph = read_graph();

    vector <int> answer;
    get_cycle(0, graph, answer);
    reverse(answer.begin(), answer.end());

    for (int i = 0; i < answer.size(); i++){
        if (i > 0) cout << "->";
        cout << answer[i];
    }

    return 0;
}
