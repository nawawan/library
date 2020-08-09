#include <bits/stdc++.h>
using namespace std;
int N;//頂点数
void waflo(){
    int d[N][N];//d[u][v]は辺e = (u, v)のコスト(d[i][i] = 0, 存在しない場合INF)
    for(int k = 0; k < N; k++){
        for(int i = 0; i < N; i++){
            for(int j = 0; j < N; j++) d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
        }
    }
}