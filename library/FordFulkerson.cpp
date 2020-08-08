#include <iostream>
#include <vector>
using namespace std;
struct edge{
    int to;
    int cap;
    int rev;
};
struct Ford{
    vector<vector<edge>> G;
    int V;
    vector<int> used;
    Ford(int N){
        V = N;
        used.resize(V, 0);
        G.resize(V);
    }
    void add(int u, int v, int c){
        edge e1 = {v, c, (int)G[v].size()};
        G[u].push_back(e1);
        edge e2 = {u, 0, (int)G[u].size() - 1};
        G[v].push_back(e2);
    }
    int dfs(int s, int t, int f){
        if(s == t) return f;
        used[s] = 1;
        for(edge &e: G[s]){
            if(used[e.to] == 0 && e.cap > 0){
                long long temp = dfs(e.to, t, min(f, e.cap));
                if(temp > 0){
                    e.cap -= temp;
                    G[e.to][e.rev].cap += temp;
                    return temp;
                }
            }
        }
        return 0;
    }
    int solve(int s, int t){
        int ans = 0;
        int INF = 1e9;
        while(1){
            used.assign(V, 0);
            int res = dfs(s, t, INF);
            if(res == 0) return ans;
            ans += res;
        }
    }
};