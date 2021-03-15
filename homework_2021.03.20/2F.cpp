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

void update_profile(string & s, int k, vector <vector<double>> & profile){
    for (int i = 0; i <= s.length() - k; i++){
        for (int j = 0; j < k; j++) profile[inv_letters[s[i+j]]][j]++;
    }
}

double get_score(int k, vector<vector<double>> & profile){
    double score = 0;
    for (int j = 0; j < k; j++){
        double maxx = 0, summ = 0;
        for (int p = 0; p < 4; p++){
            maxx = max(maxx, profile[p][j]);
            summ += profile[p][j];
        }
        score += summ - maxx;
    }
    return score;
}

void randomized_motif_search(vector <string> & dna, int k,
        vector <string> & best_motifs, double & best_score){
    vector <string> motifs;
    vector <vector<double>> profile (4, vector <double>(k, 1));
    for (string s : dna){
        int index = rand() % (s.length() - k + 1);
        string motif;
        for (int j = 0; j < k; j++) motif.push_back(s[index + j]);
        update_profile(motif, k, profile);
    }
    double score = get_score(k, profile);

    while (true) {
        vector <string> new_motifs;
        vector <vector<double>> new_profile (4, vector <double>(k, 1));
        for (string s : dna) {
            string new_motif;
            int index = get_most_probable(s, k, profile);
            for (int j = 0; j < k; j++) new_motif.push_back(s[index+j]);
            update_profile(new_motif, k, new_profile);
            new_motifs.push_back(new_motif);
        }

        double new_score = get_score(k, new_profile);
        if (score > new_score){
            score = new_score;
            motifs = new_motifs;
            profile = new_profile;
        }
        else break;
    }
    if (best_score > score){
        best_score = score;
        best_motifs = motifs;
    }
}

int main(){
    freopen("../input.txt", "r", stdin);
    freopen("../output.txt", "w", stdout);

    int k, t;
    cin >> k >> t;
    vector <string> dna(t);
    for (int i = 0; i < t; i++) cin >> dna[i];

    const double inf = 1e9;
    double best_score = inf;
    vector <string> best_motifs;

    const int max_tries = 1000;
    for (int tries = 0; tries < max_tries; tries++){
        randomized_motif_search(dna, k, best_motifs, best_score);
    }
    for (string motif : best_motifs) cout << motif << "\n";

    return 0;
}
