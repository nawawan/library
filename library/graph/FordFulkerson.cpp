#include <iostream>
#include <vector>
#include <limits>
using namespace std;
template<typename T>
struct Ford{
    struct edge{
        int to;
        T cap;
        int rev;
        edge(int t, int c, int r) : to(t), cap(c), rev(r) {}
    };
    vector<vector<edge>> G;
    T INF;
    int V;
    vector<int> used;
    Ford(int N): INF(numeric_limits<T>::max()), V(N), used(N), G(N){}
    void add(int u, int v, T c){
        G[u].emplace_back(v, c, (int)G[v].size());
        edge e2 = {u, 0, (int)G[u].size() - 1};
        G[v].emplace_back(u, 0, (int)G[u].size() - 1);
    }
    T solve(int s, int t){
        T ans = 0;
        while(1){
            used.assign(V, 0);
            int res = dfs(s, t, INF);
            if(res == 0) return ans;
            ans += res;
        }
    }
private:
    T dfs(int s, int t, T f){
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
};