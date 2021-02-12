#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main(){
    freopen("../input.txt", "r", stdin);
    freopen("../output.txt", "w", stdout);
    vector<string> patterns;
    string pattern;
    while (cin >> pattern){
        patterns.push_back(pattern);
    }
    for (auto pattern1 : patterns){
        vector <string> adjacent;
        for (auto pattern2 : patterns){
            if (pattern1 ==  pattern2) continue;
            bool equal = true;
            for (int i = 0; i + 1 < pattern1.size(); i++){
                if (pattern1[i+1] != pattern2[i]){
                    equal = false;
                    break;
                }
            }
            if (equal) adjacent.push_back(pattern2);
        }
        if (!adjacent.empty()){
            cout << pattern1 << " -> ";
            for (int i = 0; i < adjacent.size(); i++){
                if (i != 0) cout << ",";
                cout << adjacent[i];
            }
            cout << "\n";
        }
    }

    return 0;
}
