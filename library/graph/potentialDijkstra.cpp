#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <limits>
using namespace std;
typedef pair<int, int> P;
struct edge{
    int to;
    int cap;
    long long cost;
    int rev;
};
template<typename T>
struct Primal_Dual{
    int V;
    T INF;
    vector<int> pote, prevv, preve;
    vector<vector<edge>> G;
    Primal_Dual(int N): V(N), INF(numeric_limits<T>::max()), pote(V), G(V), prevv(V), preve(V){}
    void add(int s, int t, int cap, T cost){
        edge e1 = {t, cap, cost, (int)G[t].size()};
        G[s].push_back(e1);
        edge e2 = {s, 0, -cost, (int)G[s].size() - 1};
        G[t].push_back(e2);
    }
    T solve(int s, int t, T f){
        T ans = 0;
        pote.assign(V, 0);
        while(f > 0){
            priority_queue<P, vector<P>, greater<P>> q;
            vector<T> d(V, INF);
            d[s] = 0;
            q.push(P(0, s));
            while(!q.empty()){
                P v = q.top();
                q.pop();
                if(d[v.second] < v.first) continue;
                int u = v.second;
                for(int i = 0; i < (int)G[u].size(); i++){
                    edge &e = G[u][i];
                    if(e.cap > 0 && d[e.to] > d[u] - pote[e.to] + pote[u] + e.cost){
                        d[e.to] = d[u] - pote[e.to] + pote[u] + e.cost;
                        prevv[e.to] = u;
                        preve[e.to] = i;
                        q.push(P(d[e.to], e.to));
                    }
                }
            }
            if(d[t] == INF) return -1;
            for(int i = 0; i < V; i++) pote[i] += d[i];
            int temp = f;
            for(int i = t; i != s; i = prevv[i]){
                temp = min(temp, G[prevv[i]][preve[i]].cap);
            }
            f -= temp;
            ans += temp * pote[t];
            for(int i = t; i != s; i = prevv[i]){
                edge &e = G[prevv[i]][preve[i]];
                e.cap -= temp;
                G[i][e.rev].cap += temp;
            }
        }
        return ans;
    }
};