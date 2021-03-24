#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <algorithm>

using namespace std;
map <char, int> mass_spectrum_table;

map <int, int> mass_spectrum(string s, bool cyclic){
    int n = s.length();
    vector <int> spectrum(n, 0);
    map <int, int> ans;

    ans[0]++;
    for (int i = 0; i < n - 1; i++){
        vector <int> new_spectrum(n);
        for (int j = cyclic ? 0 : i; j < n; j++){
            new_spectrum[j] = spectrum[(j+n-1)%n] + mass_spectrum_table[s[j]];
            ans[new_spectrum[j]]++;
        }
        spectrum = new_spectrum;
    }
    int summ = 0;
    for (char c : s) summ += mass_spectrum_table[c];
    ans[summ]++;

    return ans;
}

int score (map <int, int> a, map <int, int> b){
    int res = 0;
    for (auto [x, y] : b){
        if (a[x] < y) return -1;
        res += y;
    }
    return res;
}

int main(){
    freopen("../input.txt", "r", stdin);
    freopen("../output.txt", "w", stdout);

    //reading mass spectrum table from the same input file
    const int table_size = 18;
    for (int i = 0; i < table_size; i++){
        char c;
        int mass;
        cin >> c >> mass;
        mass_spectrum_table[c] = mass;
    }

    int N;
    cin >> N;

    int new_mass;
    map<int, int> ideal_spectrum;
    while (cin >> new_mass){
        ideal_spectrum[new_mass]++;
    }

    int max_score = 0;
    string answer = "";
    vector <pair<int, string>> leader_board;
    leader_board.push_back({0, ""});
    while (!leader_board.empty()){
        vector <pair<int, string>> new_leader_board;
        for (auto [old_score, s] : leader_board) {
            if (old_score > max_score){
                max_score = old_score;
                answer = s;
            }
            for (auto [c, m] : mass_spectrum_table) {
                auto spectrum = mass_spectrum(s + c, false);
                int new_score = score(ideal_spectrum, spectrum);
                if (new_score != -1)
                    new_leader_board.push_back({new_score, s + c});
            }
        }
        sort(new_leader_board.begin(), new_leader_board.end());
        reverse(new_leader_board.begin(), new_leader_board.end());
        leader_board.clear();
        for (int i = 0; i < new_leader_board.size(); i++){
            if (i >= N && new_leader_board[i].first != new_leader_board[i-1].first) break;
            leader_board.push_back(new_leader_board[i]);
        }
    }
    for (int i = 0; i < answer.length(); i++){
        if (i > 0) cout << "-";
        cout << mass_spectrum_table[answer[i]];
    }
    cout << " ";

    return 0;
}
