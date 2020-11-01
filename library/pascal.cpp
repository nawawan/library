#include <bits/stdc++.h>
using namespace std;

const int MAX = 1000;
long long p[MAX][MAX];
void pascalinit(){
    p[0][0] = 1;
    for(int i = 1; i < MAX; i++){
        for(int j = 0; j < MAX; j++){
            if(j == 0) p[i][j] = 1;
            else if(j == i){
                p[i][j] = 1;
                break;
            }
            else p[i][j] = p[i - 1][j - 1] + p[i - 1][j];
        }
    }
}

long long pascal(int n, int k){
    return p[n][k];
}