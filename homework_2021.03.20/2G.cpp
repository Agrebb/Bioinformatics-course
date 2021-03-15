#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <algorithm>

using namespace std;

map<char, int> inv_letters{{'A', 0}, {'C', 1}, {'G', 2}, {'T', 3}};

int get_random_number(vector <double> & p){
    double summ = 0;
    for (double x : p) summ += x;
    int seed = rand();

    double cur_summ = 0;
    for (int j = 0; j < p.size(); j++){
        cur_summ += p[j];
        if (cur_summ * RAND_MAX > seed * summ){
            return j;
        }
    }
    return p.size() - 1;
}

int get_random_string(string & s, int k, vector <vector<int>> & profile){
    vector <double> probs;
    for (int i = 0; i <= s.length() - k; i++){
        double prob = 1;
        for (int j = 0; j < k; j++){
            prob *= profile[inv_letters[s[i+j]]][j];
        }
        probs.push_back(prob);
    }
    return get_random_number(probs);
}

void update_profile(string & s, int k, vector <vector<int>> & profile, int koef = 1){
    for (int i = 0; i <= s.length() - k; i++){
        for (int j = 0; j < k; j++) profile[inv_letters[s[i+j]]][j] += koef;
    }
}

int get_score(int k, vector<vector<int>> & profile){
    int score = 0;
    for (int j = 0; j < k; j++){
        int maxx = 0, summ = 0;
        for (int p = 0; p < 4; p++){
            maxx = max(maxx, profile[p][j]);
            summ += profile[p][j];
        }
        score += summ - maxx;
    }
    return score;
}

void gibbs_sampler(vector <string> & dna, int k, int N,
                             vector <string> & best_motifs, int & best_score){
    vector <string> motifs;
    vector <vector<int>> profile (4, vector <int>(k, 1));
    for (string s : dna){
        int index = rand() % (s.length() - k + 1);
        string motif;
        for (int j = 0; j < k; j++) motif.push_back(s[index + j]);
        update_profile(motif, k, profile);
        motifs.push_back(motif);
    }
    int score = get_score(k, profile);

    for (int step = 0; step < N; step++){
        int i = rand() % dna.size();
        auto new_profile = profile;
        update_profile(motifs[i], k, new_profile, -1);

        string new_motif;
        int index = get_random_string(dna[i], k, new_profile);
        for (int j = 0; j < k; j++) new_motif.push_back(dna[i][index+j]);
        update_profile(new_motif, k, new_profile);

        int new_score = get_score(k, new_profile);
        if (score > new_score){
            score = new_score;
            motifs[i] = new_motif;
            profile = new_profile;
        }
    }
    if (best_score > score){
        best_score = score;
        best_motifs = motifs;
    }
}

int main(){
    freopen("../input.txt", "r", stdin);
    freopen("../output.txt", "w", stdout);

    int k, t, N;
    cin >> k >> t >> N;
    vector <string> dna(t);
    for (int i = 0; i < t; i++) cin >> dna[i];

    const int inf = (int)1e9;
    int best_score = inf;
    vector <string> best_motifs;

    const int max_tries = 20;
    for (int tries = 0; tries < max_tries; tries++){
        gibbs_sampler(dna, k, N, best_motifs, best_score);
    }
    for (string motif : best_motifs) cout << motif << "\n";

    return 0;
}
