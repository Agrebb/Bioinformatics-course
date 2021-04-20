#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <assert.h>

using namespace std;

double distance (vector <vector<int>> & d, vector <int> & a, vector <int> & b){
    int summ = 0;
    for (int i : a){
        for (int j : b){
            summ += d[i][j];
        }
    }
    return (double) summ / (a.size() * b.size());
}

struct cluster{
    vector <int> indexes;
    int leaf;
};

vector <vector<int>> graph;
vector <double> age;

void unite(vector <vector<int>> & d, vector <cluster> & clusters){
    int mini, minj;
    double mindist = 1e9;
    for (int i = 0; i < clusters.size(); i++){
        auto u = clusters[i];
        for (int j = 0; j < clusters.size(); j++){
            auto v = clusters[j];
            if (i != j){
                double dist = distance(d, u.indexes, v.indexes);
                if (dist < mindist){
                    mindist = dist;
                    mini = i;
                    minj = j;
                }
            }
        }
    }
    for (int x : clusters[minj].indexes){
        clusters[mini].indexes.push_back(x);
    }

    age.push_back(mindist / 2);
    int maxleaf = graph.size();
    graph.push_back(vector <int>());
    graph[maxleaf].push_back(clusters[mini].leaf);
    graph[maxleaf].push_back(clusters[minj].leaf);
    clusters[mini].leaf = maxleaf;
    clusters.erase(clusters.begin() + minj);
}

int main() {
    freopen("../input.txt", "r", stdin);
    freopen("../output.txt", "w", stdout);

    int n; cin >> n;
    vector <vector <int>> d(n, vector <int>(n));
    for (int i = 0; i < n; i++){
        for (int k = 0; k < n; k++){
            cin >> d[i][k];
        }
    }

    graph.resize(n);
    age.resize(n);
    vector <cluster> clusters;
    for (int i = 0; i < n; i++){
        clusters.push_back(cluster{{i}, i});
    }
    for (int i = 0; i < n - 1; i++){
        unite(d, clusters);
    }
    cout.precision(3);
    for (int v = 0; v < graph.size(); v++){
        for (auto u : graph[v]){
            double w = abs(age[u] - age[v]);
            cout << v << "->" << u << ":" << fixed << w << endl;
            cout << u << "->" << v << ":" << fixed << w << endl;
        }
    }

    return 0;
}
