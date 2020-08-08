#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> P;
long long INF = 1e14;
struct edge{
    int to;
    int cost;
};
int N, M;//Vは頂点、Eは辺の数
void solve(){//priority_queueを用いる
    long long d[N];//各頂点までの距離
    priority_queue<P, vector<P>, greater<P>> que;
    vector<edge> G[N];
    fill(d, d + N, INF);
    for(int i = 0; i < M; i++){
        int a, b, cs;
        cin >> a >> b >> cs;
        a--;
        b--;
        edge e = {a, cs}, e2 = {b, cs};
        G[a].push_back(e2);
        G[b].push_back(e);
    }
    int s = 0;//スタート地点は最初0
    d[s] = 0;
    que.push(P(0, 0));
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
    cout << d[N - 1] << endl;
}

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