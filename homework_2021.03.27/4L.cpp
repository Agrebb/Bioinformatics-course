#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <algorithm>

using namespace std;

int main(){
    freopen("../input.txt", "r", stdin);
    freopen("../output.txt", "w", stdout);

    vector <int> spectrum;
    vector <int> convolution;
    int mass;
    while (cin >> mass){
        spectrum.push_back(mass);
    }
    for (int x : spectrum){
        for (int y : spectrum){
            if (x > y) {
                convolution.push_back(x - y);
            }
        }
    }
    for (int diff : convolution) cout << diff << " ";

    return 0;
}
