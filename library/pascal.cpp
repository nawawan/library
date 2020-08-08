#include <bits/stdc++.h>
using namespace std;

long long N = 1000;
vector<vector<double>> p(N, vector<double>(N, 0));
void pascalinit(long long N){
    p[0][0] = 1;
    for(int i = 1; i < N; i++){
        for(int j = 0; j < N; j++){
            if(j == 0) p[i][j] = 1;
            else if(j == i){
                p[i][j] = 1;
                break;
            }
            else p[i][j] = p[i - 1][j - 1] + p[i - 1][j];
        }
    }
}

double pascal(int n, int k){
    return p[n][k];
}