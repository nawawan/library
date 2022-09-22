#include <iostream>
#include <vector>
#include <queue>
#include <limits>
using namespace std;
template<typename T>
struct Dinic{
    struct edge{
        int to;
        T cap;
        int rev;
        edge(int t, T c, int r) : to(t), cap(c), rev(r) {}
    };
    Dinic(int N): INF(numeric_limits<T>::max()), V(N), used(N), level(N), G(N){}
    void add(int u, int v, T c){
        G[u].emplace_back(v, c, (int)G[v].size());
        G[v].emplace_back(u, 0, (int)G[u].size() - 1);
        p.emplace_back(u, (int)G[u].size() - 1);
    }
    T solve(int s, int t){
        T flow = 0;
        while(1){
            bfs(s);
            if(level[t] < 0) return flow;
            used.assign(V, 0);
            long long f;
            while((f = dfs(s, t, INF)) > 0) flow += f;
        }
    }
    edge get_edge(int i){
        pair<int, int> pos = p[i];
        edge e = G[p[i].first][p[i].second];
        return e;
    }
    void change_edge(int i, T new_cap){
        pair<int, int> pos = p[i];
        edge &e = G[p[i].first][p[i].second];
        e.cap = new_cap;
        G[e.to][e.rev].cap = -new_cap;
    }
private:
    int V;
    T INF;
    vector<int> level, used;
    vector<vector<edge>> G;
    vector<pair<int, int>> p; 
    void bfs(int s){
        level.assign(V, -1);
        queue<int> q;
        q.push(s);
        level[s] = 0;
        while(!q.empty()){
            int v = q.front();
            q.pop();
            for(edge e: G[v]){
                if(e.cap > 0 && level[e.to] < 0){
                    level[e.to] = level[v] + 1;
                    q.push(e.to);
                }
            }
        }
    }
    T dfs(int s, int t, T f){
        if(s == t) return f;
        for(int &i = used[s]; i < (int)G[s].size(); i++){
            edge &e = G[s][i];
            if(e.cap > 0 && level[e.to] > level[s]){
                T d = dfs(e.to, t, min(f, e.cap));
                if(d > 0){
                    e.cap -= d;
                    G[e.to][e.rev].cap += d;
                    return d;
                }
            }
        }
        return 0;
    }
};


//dfs部分、これでも変わらないっぽい？
    /*int dfs(int s, int t, int f){
        if(s == t) return f;
        used[s] = 1;
        for(edge &e: G[s]){
            if(used[e.to] == 0 && e.cap > 0 && level[e.to] > level[s]){
                int d = dfs(e.to, t, min(f, e.cap));
                if(d > 0){
                    e.cap -= d;
                    G[e.to][e.rev].cap += d;
                    return d;
                }
            }   
        }
        return 0;
    }*/