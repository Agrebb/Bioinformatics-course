#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <assert.h>

using namespace std;

double distance(vector<vector<double>> & points, int i, int j){
    double result = 0;
    for (int coord = 0; coord < points[i].size(); coord++){
        result += (points[i][coord] - points[j][coord])*(points[i][coord] - points[j][coord]);
    }
    return result;
}

vector <int> k_first_traversal(vector <vector<double>> & points, int k){
    int n = points.size();

    vector <bool> is_center(n, false);
    vector <int> centers = {0};
    is_center[0] = true;

    while (centers.size() < k) {
        double maxdist = 0;
        int maxi;
        for (int i = 0; i < n; i++) {
            if (!is_center[i]) {
                double mindist = 1e9;
                for (int j : centers) {
                    double dist = distance(points, i, j);
                    mindist = min(mindist, dist);
                }
                if (mindist > maxdist) {
                    maxdist = mindist;
                    maxi = i;
                }
            }
        }
        centers.push_back(maxi);
        is_center[maxi] = true;
    }

    return centers;
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

    auto centers = k_first_traversal(points, k);

    cout.precision(3);
    for (int i : centers){
        for (double coord : points[i]){
            cout << fixed << coord << " ";
        }
        cout << endl;
    }

    return 0;
}
