#include <iostream>
#include <vector>
#include <queue>
#include <limits>
using namespace std;
struct edge{
    int to;
    int cost;
};
template<typename T>
struct dijkstra{//priority_queueを用いる
    typedef pair<T, int> P;
    vector<vector<edge>> G;
    vector<T> d;
    T INF = numeric_limits<T>::max();
    int n;
    dijkstra(int N){
        G.resize(N);
        d.resize(N, INF);
        n = N;
    }
    dijkstra(vector<vector<edge>>&g) : G(g), n(g.size()){
        d.resize(n, INF);
    }
    void add(int x, int y, T cost1){//ここ注意
        edge e1 = {x, cost1}, e2 = {y, cost1};
        G[x].push_back(e2);
        G[y].push_back(e1);
    }
    void solve(int s){
        priority_queue<P, vector<P>, greater<P>> que;
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