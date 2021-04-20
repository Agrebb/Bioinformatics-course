#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <assert.h>

using namespace std;

int main() {
    freopen("../input.txt", "r", stdin);
    freopen("../output.txt", "w", stdout);

    int n, j; cin >> n >> j;
    vector <vector <int>> d(n, vector <int>(n));
    for (int i = 0; i < n; i++){
        for (int k = 0; k < n; k++){
            cin >> d[i][k];
        }
    }
    int i = (j == 0) ? 1 : 0;
    const int inf = 1e9;
    int min_length = inf;
    for (int k = 0; k < n; k++){
        if (k == i || k == j) continue;
        min_length = min(min_length, (d[i][j] + d[j][k] - d[i][k]) / 2);
    }
    cout << min_length;

    return 0;
}
