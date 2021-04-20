#include <vector>
#include <iostream>
#include <limits>
using namespace std;
template<typename T>
struct primal{
    struct edge{
        int to;
        int cap;
        T cost;
        int inv;
    };
    T INF;
    int V;
    vector<int> prevv, preve;
    vector<vector<edge>> G;
    primal(int N): V(N), prevv(N), preve(N), G(N), INF(numeric_limits<T>::max()){}
    void add(int s, int t, int cap, T cost){
        edge e1 = {t, cap, cost, (int)G[t].size()};
        G[s].push_back(e1);
        edge e2 = {s, 0, -cost, (int)G[s].size() - 1};
        G[t].push_back(e2);
    }
    T solve(int s, int t, T f){
        T res = 0;
        vector<T> d(V);
        while(f > 0){
            bool update = true;
            d.assign(V, INF);
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