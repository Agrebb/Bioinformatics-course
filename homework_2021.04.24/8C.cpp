#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <assert.h>

using namespace std;

double distance (vector <double> & a, vector <double> & b){
    double result = 0;
    for (int i = 0; i < a.size(); i++)
        result += (a[i] - b[i])*(a[i] - b[i]);
    return result;
}

void centers_to_clusters(vector <vector<double>> & points,
        vector <vector<double>> & centers, vector <vector <int>> & clusters, int k){
    clusters.clear();
    clusters.resize(k);
    for (int i = 0; i < points.size(); i++){
        double mindist = 1e9;
        int minj;
        for (int j = 0; j < k; j++){
            double dist = distance(points[i], centers[j]);
            if (dist < mindist){
                mindist = dist;
                minj = j;
            }
        }
        clusters[minj].push_back(i);
    }
}

void clusters_to_centers(vector <vector<double>> & points,
        vector <vector<double>> & centers, vector <vector <int>> & clusters, int k){
    centers.clear();
    centers.resize(k);
    int m = points[0].size();
    for (int j = 0; j < k; j++){
        vector <double> mass_center(m, 0);
        for (int i : clusters[j]){
            for (int coord = 0; coord < m; coord++){
                mass_center[coord] += points[i][coord] / clusters[j].size();
            }
        }
        centers[j] = mass_center;
    }
}

int main() {
    freopen("../input.txt", "r", stdin);
    freopen("../output.txt", "w", stdout);

    int k, m; cin >> k >> m;
    vector <vector <double>> points;
    double x;
    while (cin >> x){
        int cur = points.size();
        points.push_back(vector <double>(m));
        points[cur][0] = x;
        for (int i = 1; i < m; i++) cin >> points[cur][i];
    }

    vector <vector<double>> centers(k);
    for (int j = 0; j < k; j++) centers[j] = points[j];
    vector <vector<int>> clusters;

    const int num_steps = 100;
    for (int step = 0; step < num_steps; step++){
        centers_to_clusters(points, centers, clusters, k);
        clusters_to_centers(points, centers, clusters, k);
    }

    cout.precision(3);
    for (auto center : centers){
        for (double x : center){
            cout << fixed << x << " ";
        }
        cout << endl;
    }

    return 0;
}
