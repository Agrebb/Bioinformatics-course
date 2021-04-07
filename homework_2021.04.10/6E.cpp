#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

map<char, char> invert{{'A', 'T'}, {'T', 'A'}, {'C', 'G'}, {'G', 'C'}};

int main() {
    freopen("../input.txt", "r", stdin);
    freopen("../output.txt", "w", stdout);

    int k;
    string s, t;
    cin >> k >> s >> t;
    for (int i = 0; i <= s.length() - k; i++){
        for (int j = 0; j <= t.length() - k; j++){
            bool eq1 = true, eq2 = true;
            for (int p = 0; p < k; p++){
                eq1 &= (s[i+p] == t[j+p]);
                eq2 &= (s[i+p] == invert[t[j+k-p-1]]);
                if (!eq1 && !eq2) break;
            }
            if (eq1 || eq2) cout << "(" << i << ", " << j << ")\n";
        }
    }

    return 0;
}
