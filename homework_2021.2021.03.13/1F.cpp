#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main(){
    freopen("../input.txt", "r", stdin);
    freopen("../output.txt", "w", stdout);

    string s;
    cin >> s;
    int bal = 0, min_bal = s.length() + 1;
    vector <int> ans;
    for (int i = 0; i < s.length(); i++){
        if (s[i] == 'G') bal++;
        else if (s[i] == 'C') bal--;
        if (min_bal > bal){
            min_bal = bal;
            ans.clear();
            ans.push_back(i);
        }
        else if (min_bal == bal) ans.push_back(i);
    }
    for (int index : ans) cout << index + 1 << " ";

    return 0;
}
