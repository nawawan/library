#include <bits/stdc++.h>
using namespace std;
long long INF = 100000000;
int N;
typedef pair<int, int> P;//firstは最短距離、secondは頂点
struct edge{
    int to;
    int cost;
};

void prim(){
    int V, E;
    cin >> V >> E;
    vector<edge> G[V];
    for(int i = 0; i < E; i++){
        int s, t, w;
        cin >> s >> t >> w;
        edge e ={s, w}, e2 = {t, w};
        G[t].push_back(e);
        G[s].push_back(e2);
    }
    priority_queue<P, vector<P>, greater<P>> q;
    vector<int> used(V, 0);
    int ans = 0;
    q.push(P(0, 0));
    while(!q.empty()){
        P v = q.top();
        q.pop();
        if(used[v.second] == 1) continue;
        ans += v.first;
        used[v.second] = 1;
        for(edge e: G[v.second]){
            q.push(P(e.cost, e.to));
        }
    }
    cout << ans << endl;
}

/*priority_queueを使わないダイクストラ的prim
void prim(){
    long long V, E;
    cin >> V >> E;
    vector<edge> G[V];
    for(int i = 0; i < E; i++){
        int s, t, w;
        cin >> s >> t >> w;
        edge e ={t, w}, e2 = {s, w};
        G[s].push_back(e);
        G[t].push_back(e2);
    }
    vector<int> used(V, 0);
    vector<int> mincost(V, INF);//木からの最短距離
    int ans = 0;
    mincost[0] = 0;
    while(1){
        int v = -1;
        for(int i = 0; i < V; i++){
            if(!used[i] && (v == -1 || mincost[v] > mincost[i])) v = i;
        }
        if(v == -1) break;
        ans += mincost[v];
        used[v] = 1;
        for(edge e: G[v]){
            mincost[e.to] = min(mincost[e.to], e.cost);
        }
    }
    std::cout << ans << std::endl;
}
*/