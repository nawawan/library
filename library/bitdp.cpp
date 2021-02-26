#include <iostream>
#include <vector>
using namespace std;
long long INF = 1e18;
vector<vector<long long>> dp;
int N;
vector<vector<long long>> cost;
//dp配列は初期値が-1
long long dfs(int bit, int now, vector<vector<long long>> &dp, vector<vector<long long>>&cost, int N){
    if(dp[bit][now] >= 0) return dp[bit][now];
    if(bit == (1 << N) - 1 && now == 0) return dp[bit][now] = 0;
    long long res = INF;
    for(int u = 0; u < N; u++){
        if(!(bit & (1 << u))){
            res = min(res, dfs(bit | (1 << u), u, dp, cost, N) + cost[now][u]);
        }
    }
    return dp[bit][now] = res; 
}