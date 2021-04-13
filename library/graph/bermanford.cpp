#include <iostream>
#include <vector>
using namespace std;
long long INF = 1000000000000000000;
struct edge{
    int from;
    int to;
    long long cost;
};
/*
N : ノード数, M : 辺の数, es : 辺の情報
s : 始点, t : 終点
O(NM)
*/
void solve(int N, int M, vector<edge> &es, int s, int t){
    vector<long long> d(N);//各頂点までの距離
    for(int i = 0; i < N; i++) d[i] = INF;
    d[s] = 0;
    long long k = 0;
    long long ans = 0;
    while(true){
        bool flag = false;
        for(int i = 0; i < M; i++){
            edge e = es[i];
            if(d[e.from] != INF && d[e.to] > d[e.from] + e.cost){
                d[e.to] = d[e.from] + e.cost;
                flag = true;
            }
        }
        if(!flag || k == N) break;
        k++;
    }
    ans = min(ans, d[t]);
    k = 0;
    vector<bool> judge(N, false);
    while(true){
        for(int i = 0; i < M; i++){
            edge e = es[i];
            if(d[e.from] != INF && d[e.to] > d[e.from] + e.cost){
                judge[e.to] = true;
            }
            if(judge[e.from]) judge[e.to] = true;
        }
        k++;
        if(k == N) break;
    }
    if(judge[t]) cout << -1 << endl;
    else cout << -ans << endl;
}