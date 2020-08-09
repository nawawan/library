#include <vector>
#include <iostream>
using namespace std;
struct edge{
    int to;
    int cap;
    int cost;
    int inv;
};
struct primal{
    int INF;
    int V;
    vector<int> prevv, preve;
    vector<vector<edge>> G;
    primal(int N){
        V = N;
        prevv.resize(V);
        preve.resize(V);
        G.resize(V);
        INF = 1e9;
    }
    void add(int s, int t, int cap, int cost){
        edge e1 = {t, cap, cost, (int)G[t].size()};
        G[s].push_back(e1);
        edge e2 = {s, 0, -cost, (int)G[s].size() - 1};
        G[t].push_back(e2);
    }
    int solve(int s, int t, int f){
        int res = 0;
        while(f > 0){
            vector<int> d(V, INF);
            bool update = true;
            d[s] = 0;
            while(update){
                update = false;
                for(int i = 0; i < V; i++){
                    if(d[i] == INF) continue;
                    for(int j = 0; j < (int)G[i].size(); j++){
                        edge e = G[i][j];
                        if(e.cap > 0 && d[e.to] > d[i] + e.cost){
                            d[e.to] = d[i] + e.cost;
                            prevv[e.to] = i;
                            preve[e.to] = j;
                            update = true;
                        }
                    }
                }
            }
            if(d[t] == INF) return -1;
            int dmin = f;
            for(int v = t; v != s; v = prevv[v]){
                dmin = min(dmin, G[prevv[v]][preve[v]].cap);
            }
            f -= dmin;
            res += d[t] * dmin;
            for(int v = t; v != s; v = prevv[v]){
                edge &e = G[prevv[v]][preve[v]];
                e.cap -= dmin;
                G[v][e.inv].cap += dmin;
            }
        }
        return res;
    }
};