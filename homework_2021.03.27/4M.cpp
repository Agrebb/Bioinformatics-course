#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <algorithm>

using namespace std;

map <int, int> mass_spectrum(vector <int> & s, bool cyclic){
    int n = s.size();
    vector <int> spectrum(n, 0);
    map <int, int> ans;

    ans[0]++;
    for (int i = 0; i < n - 1; i++){
        vector <int> new_spectrum(n);
        for (int j = cyclic ? 0 : i; j < n; j++){
            new_spectrum[j] = spectrum[(j+n-1)%n] + s[j];
            ans[new_spectrum[j]]++;
        }
        spectrum = new_spectrum;
    }
    int summ = 0;
    for (int x : s) summ += x;
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

    int M, N;
    cin >> M >> N;

    int new_mass;
    map<int, int> ideal_spectrum;
    vector <int> ideal_spectrum_v;
    while (cin >> new_mass){
        ideal_spectrum[new_mass]++;
        ideal_spectrum_v.push_back(new_mass);
    }

    vector <int> letters;
    map <int, int> freq;
    for (int x : ideal_spectrum_v){
        for (int y : ideal_spectrum_v){
            if (x > y) {
                freq[x-y]++;
            }
        }
    }

    vector <pair<int, int>> freq_v;
    for (auto [val, frequency] : freq) freq_v.push_back({frequency, val});
    sort(freq_v.begin(), freq_v.end());
    reverse(freq_v.begin(), freq_v.end());
    for (int i = 0; i < freq_v.size(); i++){
        int letter = freq_v[i].second;
        if (letter >= 57 && letter <= 200) {
            if (letters.size() >= M && freq_v[i].first != freq_v[i - 1].first) break;
            letters.push_back(letter);
        }
    }

    int max_score = 0;
    vector <int> answer;
    vector <pair<int, vector <int>>> leader_board;
    leader_board.push_back({0, vector <int>()});
    while (!leader_board.empty()){
        vector <pair<int, vector <int>>> new_leader_board;
        for (auto [old_score, s] : leader_board) {
            if (old_score > max_score){
                max_score = old_score;
                answer = s;
            }
            for (int letter : letters) {
                s.push_back(letter);
                auto spectrum = mass_spectrum(s, false);
                int new_score = score(ideal_spectrum, spectrum);
                if (new_score != -1)
                    new_leader_board.push_back({new_score, s});
                s.pop_back();
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
    for (int i = 0; i < answer.size(); i++){
        if (i > 0) cout << "-";
        cout << answer[i];
    }
    cout << " ";

    return 0;
}
