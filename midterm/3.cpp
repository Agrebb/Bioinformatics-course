#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <queue>

using namespace std;

//from 4I


map <int, int> mass_spectrum(vector <int> s, bool cyclic){
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
    for (int c : s) summ += c;
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

//from 3J

void get_cycle(string v, map<string, vector<string>> & graph, vector <string> & answer){
    for (int i = 0; i < graph[v].size(); i++){
        string u = graph[v][i];
        if (u != ""){
            graph[v][i] = "";
            get_cycle(u, graph, answer);
        }
    }
    answer.push_back(v);
}

int recover (char c){
    int x = (int) c;
    if (x < 0) x = 256 + x;
    return x;
}

int main(){
    freopen("../input.txt", "r", stdin);
    freopen("../output.txt", "w", stdout);

    // from 4M

    int k, M, N;
    cin >> k >> M >> N;

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

    //from scratch

    vector <int> cur(k, 0);
    vector <pair<int, vector <int>>> sorted;
    while (true){
        vector <int> s(k);
        for (int i = 0; i < k; i++) s[i] = letters[cur[i]];
        auto spectrum = mass_spectrum(s, false);
        int sc = score(ideal_spectrum, spectrum);
        if (sc != -1){
            sorted.push_back({sc, s});
        }

        bool ok = false;
        for (int i = 0; i < k; i++){
            if (cur[i] + 1 < letters.size()){
                cur[i]++;
                ok = true;
                break;
            }
            else{
                cur[i] = 0;
            }
        }
        if (!ok) break;
    }
    sort(sorted.begin(), sorted.end());
    reverse(sorted.begin(), sorted.end());

    vector <string> kmers;
    for (int i = 0; i < sorted.size(); i++){
        if (i >= N && sorted[i].first != sorted[i-1].first) break;
        string kmer;
        for (int x : sorted[i].second){
            kmer.push_back((char)(x));
        }
        kmers.push_back(kmer);
    }

    //from 3J

    map<string, vector<string>> graph;
    map <string, int> in, out;
    for (string s : kmers){
        string s1, s2;
        for (int i = 0; i < k - 1; i++){
            s1.push_back(s[i]);
            s2.push_back(s[i+1]);
        }
        graph[s1].push_back(s2);
        out[s1]++; in[s2]++;

        graph[s2] = graph[s2]; // we want add s2 to map if it wasn't there, and not to change anything otherwise
    }

    map<string, int> balance;
    for (auto vertex : graph){
        for (string neighbour : vertex.second){
            balance[vertex.first]++;
            balance[neighbour]--;
        }
    }

    string head = "", tail = "";
    int case_num = 0; // 0 - cycle, 1 - path, 2 - none
    for (auto vertex : graph){
        string v = vertex.first;
        if (balance[v] < 0){
            if (head == "" && case_num != 2){
                head = v;
                case_num = 1;
            }
            else case_num = 2;
        }
        if (balance[v] > 0){
            if (tail == "" && case_num != 2){
                tail = v;
                case_num = 1;
            }
            else case_num = 2;
        }
    }
    if (case_num == 1) graph[head].push_back(tail);

    if (case_num != 2) {
        vector <string> answer;
        get_cycle((graph.begin()->first), graph, answer);
        reverse(answer.begin(), answer.end());
        answer.pop_back();

        int start_index = 0;
        for (int i = 0; i < answer.size(); i++){
            if (answer[i] == head && answer[(i+1) % answer.size()] == tail)
                start_index = i+1;
        }
        vector <int> masses;
        for (int i = 0; i < answer.size(); i++){
            if (i == 0){
                for (char c : answer[(i + start_index) % answer.size()]) masses.push_back(recover(c));
            }
            masses.push_back(recover(answer[(i + start_index) % answer.size()].back()));
        }
        for (int i = 0; i < masses.size(); i++){
            if (i > 0) cout << "-";
            cout << masses[i];
        }
        cout << "\n";
        cout << score(ideal_spectrum, mass_spectrum(masses, case_num == 0)) << "\n";
        cout << "\n";
    }
    else{
        //from 3K

        vector <string> paths;
        for (auto vertex : graph){
            string v = vertex.first;
            if (out[v] != 1 || in[v] != 1){
                for (int i = 0; i < vertex.second.size(); i++){
                    string u = vertex.second[i];
                    if (u == "") continue;

                    string path = v + u.back();
                    graph[v][i] = "";
                    while (out[u] == 1 && in[u] == 1){
                        string next_u = graph[u][0];
                        if (next_u == "") break;
                        graph[u][0] = "";
                        u = next_u;
                        path.push_back(u.back());
                    }
                    paths.push_back(path);
                }
            }
        }

        for (string path : paths){
            vector <int> masses;
            for (char c : path){
                masses.push_back(recover(c));
            }
            for (int i = 0; i < masses.size(); i++){
                if (i > 0) cout << "-";
                cout << masses[i];
            }
            cout << "\n";
            cout << score(ideal_spectrum, mass_spectrum(masses, false)) << "\n";
            cout << "\n";
        }
    }

    return 0;
}
