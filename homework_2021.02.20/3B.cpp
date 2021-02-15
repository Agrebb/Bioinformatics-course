#include <iostream>
#include <string>

using namespace std;

int main(){
    freopen("../input.txt", "r", stdin);
    freopen("../output.txt", "w", stdout);
    string s;
    cin >> s;
    cout << s;
    while (cin >> s){
        cout << s.back();
    }

    return 0;
}
