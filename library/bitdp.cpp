#include <iostream>
#include <vector>
using namespace std;
long long dfs(int bit, int now){
    if(dp[bit][now] >= 0) return dp[bit][now];
    if(bit == (1 << N) - 1 && now == 0) return dp[bit][now] = 0;
    long long res = INF;
    for(int u = 0; u < N; u++){
        if(!(bit & (1 << u))){
            res = min(res, dfs(bit | (1 << u), u) + cost[now][u]);
        }
    }
    return dp[bit][now] = res; 
}
long long dfs(int bit, int v){//vに行く時の最小値を返す
    if(bit == 0){//初期位置を0とする
        if(v == 0) return 0;
        else return INF;
    }
    //std::cout << dp[bit][v] << std::endl;
    if(dp[bit][v] != INF) return dp[bit][v];//探索済の場合
    if(!(bit & (1 << v))) return INF;
    int prebit = bit ^(1 << v);//vを除いた集合
    long long res = INF + 1;//答えを格納
    for(int u = 0; u < N; u++){//vの前に来る街を探索
        res = min(res, dfs(prebit, u) + cost[u][v]);//値の更新
    }
    return dp[bit][v] = res;
}