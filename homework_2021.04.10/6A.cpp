#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

void out(vector <int> & p){
    for (int i = 0; i < p.size(); i++){
        if (p[i] > 0) cout << '+';
        cout << p[i];
        if (i + 1 < p.size()) cout << " ";
    }
    cout << "\n";
}

void apply(vector <int> & p, int i, int j){
    reverse(p.begin() + i, p.begin() + j + 1);
    for (int k = i; k <= j; k++) p[k] *= -1;
    out(p);
}

int main() {
    freopen("../input.txt", "r", stdin);
    freopen("../output.txt", "w", stdout);

    vector <int> p;
    int x;
    while (cin >> x) p.push_back(x);

    for (int i = 0; i < p.size(); i++){
        if (abs(p[i]) != i + 1){
            for (int j = i + 1; j < p.size(); j++){
                if (abs(p[j]) == i + 1){
                    apply(p, i, j);
                    break;
                }
            }
        }
        if (p[i] == -(i+1)){
            p[i] *= -1;
            out(p);
        }
    }

    return 0;
}
