#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <algorithm>

using namespace std;

map<char, int> inv_letters{{'A', 0}, {'C', 1}, {'G', 2}, {'T', 3}};

int get_most_probable (string & s, int k, vector<vector<double>> & profile){
    double max_prob = 0;
    int index = 0;
    for (int i = 0; i <= s.length() - k; i++){
        double prob = 1;
        for (int j = 0; j < k; j++){
            prob *= profile[inv_letters[s[i+j]]][j];
        }
        if (max_prob < prob){
            max_prob = prob;
            index = i;
        }
    }
    return index;
}

int main(){
    freopen("../input.txt", "r", stdin);
    freopen("../output.txt", "w", stdout);

    string s;
    cin >> s;
    int k;
    cin >> k;
    vector <vector<double>> profile(4, vector<double>(k, 0));
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < k; j++){
            cin >> profile[i][j];
        }
    }
    int index = get_most_probable(s, k, profile);
    for (int j = 0; j < k; j++) cout << s[index+j];

    return 0;
}
