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
    for (int i = 0; i <= dna[0].length() - k; i++){
        vector <string> motifs;

        vector <vector<double>> profile (4, vector <double>(k, 1));
        string new_motif;
        for (int j = 0; j < k; j++) new_motif.push_back(dna[0][i+j]);
        update_profile(new_motif, k, profile);
        motifs.push_back(new_motif);

        for (int p = 1; p < t; p++){
            int index = get_most_probable(dna[p], k, profile);
            new_motif.clear();
            for (int j = 0; j < k; j++) new_motif.push_back(dna[p][index+j]);
            update_profile(new_motif, k, profile);
            motifs.push_back(new_motif);
        }

        double score = 0;
        for (int j = 0; j < k; j++){
            double maxx = 0, summ = 0;
            for (int p = 0; p < 4; p++){
                maxx = max(maxx, profile[p][j]);
                summ += profile[p][j];
            }
            score += summ - maxx;
        }
        if (best_score > score){
            best_score = score;
            best_motifs = motifs;
        }
    }
    for (string motif : best_motifs) cout << motif << "\n";

    return 0;
}
