#include <iostream>
#include <vector>
using namespace std;//計算量は(NW)
long long N, W;
vector<long long> w, v;
vector<vector<long long>> dp;//dp[i][j]はi番目以降から重さがj以下となるように選んだときの価値
long long rec(int i, int j){
    long long res;
    if(dp[i][j] > 0) return dp[i][j];
    if(i == N) res = 0;
    else if(j < w[i]) return rec(i + 1, j);
    else{
        res = max(rec(i + 1, j), rec(i + 1, j - w[i] + v[i]));
    }
    dp[i][j] = res;
    return dp[i][j];
}
//または
/*
for(int i = N - 1; i >= 0; i++){
    for(int j = 0; j < W; j++){
        if(j < w[i]) dp[i][j] = dp[i + 1][j];
        else{
            dp[i][j] = max(dp[i + 1][j], dp[i + 1][j - w[i]] + v[i]);
        }
    }
}
 */

//Wがとても大きい場合
vector<vector<long long>> dp;//dp[i + 1][j]でi番目までのうち価値がjとなるように選んだときの重さの最小
    /* for(int i = 0; i < N ; i++){
        for(int j = 0; j < 100001; j++){
            if(j < v[i]) dp[i + 1][j] = dp[i][j];
            else{
                dp[i + 1][j] = min(dp[i][j], dp[i][j - v[i]] + w[i]);
            }
        }
    }*/

//制限個数なしのナップザック
/*
for(int i = 0; i < N; i++){
    for(int j = 0; j <= W; j++){
        if(j < w[i]) dp[i + 1][j] = dp[i][j];
        else dp[i + 1][j] = max(dp[i][j], dp[i + 1][j - w[i]] + v[i]);
    }
}
 */