#include <iostream>
#include <string>

using namespace std;

int main(){
    freopen("../input.txt", "r", stdin);
    freopen("../output.txt", "w", stdout);
    int k;
    cin >> k;
    string s;
    cin >> s;
    for (int i = 0; i < s.length() - k + 1; i++){
        for (int j = 0; j < k; j++) cout << s[i+j];
        cout << "\n";
    }

    return 0;
}

