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

    int n = p.size() / 2;
    vector <int> p_new(n);
    for (int i = 0; i < n; i++) p_new[i] = p[i+n];
    while (p.size() > n) p.pop_back();

    for (int i = 0; i < n; i++){
        if (abs(p[i]) != abs(p_new[i])){
            for (int j = i + 1; j < n; j++){
                if (abs(p[j]) == abs(p_new[i])){
                    apply(p, i, j);
                    break;
                }
            }
        }
        if (p[i] != p_new[i]){
            p[i] *= -1;
            out(p);
        }
    }

    return 0;
}
