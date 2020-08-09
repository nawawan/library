#include <iostream>
#include <vector>
#include <queue>
using namespace std;
struct edge{
    int to;
    long long cap;
    int rev;
};
struct Dinic{
    int V;
    vector<int> level, used;
    vector<vector<edge>> G;
    Dinic(int N){
        V = N;
        used.resize(V, 0);
        level.resize(V, -1);
        G.resize(V);
    }
    void add(int u, int v, long long c){
        edge e1 = {v, c, (int)G[v].size()};
        G[u].push_back(e1);
        edge e2 = {u, 0, (int)G[u].size() - 1};
        G[v].push_back(e2);
    }
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
    long long dfs(int s, int t, long long f){
        if(s == t) return f;
        for(int &i = used[s]; i < (int)G[s].size(); i++){
            edge &e = G[s][i];
            if(e.cap > 0 && level[e.to] > level[s]){
                long long d = dfs(e.to, t, min(f, e.cap));
                if(d > 0){
                    e.cap -= d;
                    G[e.to][e.rev].cap += d;
                    return d;
                }
            }
        }
        return 0;
    }
    int solve(int s, int t){
        int flow = 0;
        int INF = 1e9;
        while(1){
            bfs(s);
            if(level[t] < 0) return flow;
            used.assign(V, 0);
            int f;
            while((f = dfs(s, t, INF)) > 0) flow += f;
        }
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