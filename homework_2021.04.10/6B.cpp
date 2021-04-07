#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

int main() {
    freopen("../input.txt", "r", stdin);
    freopen("../output.txt", "w", stdout);

    int prev = 0, cur;
    int cnt = 0, n = 0;
    while (cin >> cur){
        if (cur != prev + 1) cnt++;
        prev = cur;
        n++;
    }
    if (prev != n) cnt++;
    cout << cnt << "\n";

    return 0;
}
