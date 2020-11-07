#include <bits/stdc++.h>
using namespace std;
typedef pair<long long, int> P;
struct edge{
    int to;
    long long cost;
};
struct dijkstra{//priority_queueを用いる
    vector<vector<edge>> G;
    vector<long long> d;
    long long INF;
    int n;
    dijkstra(int N){
        G.resize(N);
        INF = 1e14;
        d.resize(N, INF);
        n = N;
    }
    void add(int x, int y, long long cost1){//ここ注意
        edge e1 = {x, cost1}, e2 = {y, cost1};
        G[x].push_back(e2);
        G[y].push_back(e1);

    }
    void solve(){
        priority_queue<P, vector<P>, greater<P>> que;
        int s = 0;//スタート地点
        d[s] = 0;
        que.push(P(0, s));
        while(!que.empty()){
            P p = que.top();
            que.pop();
            int v = p.second;
            if(d[v] < p.first) continue;
            for(int i = 0; i < G[v].size(); i++){
                edge e = G[v][i];
                if(d[e.to] > d[v] + e.cost){
                    d[e.to] = d[v] + e.cost;
                    que.push(P(d[e.to], e.to));
                }
            }
        }
        cout << d[n - 1] << endl;
    }
};

/*
void solve(int a, int b){
    vector<int> used(n, 0);
    vector<long long> dis(n, INF);
    dis[a] = 0;
    while(1){
        int s = -1;
        long long d = INF;
        for(int i = 0; i < n; i++){
            if(used[i] == 0 && d > dis[i]) {
                s = i;
                d = dis[i];
            }
        }
        if(s == -1) break;
        used[s] = 1;
        for(edge e: G[s]){
            dis[e.to] = min(dis[e.to], dis[s] + e.cost);
        }
    }
    if(dis[b] == INF) cout << -1 << endl;
    else cout << dis[b] << endl;
}
 */