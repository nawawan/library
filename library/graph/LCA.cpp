#include <vector>
using namespace std;
struct LCA{
    vector<vector<int>> parent;
    vector<int> depth;
    vector<vector<int>> G;
    int N;
    LCA(){}
    LCA(vector<vector<int>> &g) : N(g.size()), depth(g.size()), G(g){
        parent.resize(25, vector<int>(N));
    }
    LCA(int n): N(n), depth(n), G(n){
        parent.resize(41, vector<int>(n));
    }
    void add_edge(int u, int v){
        G[u].push_back(v);
        G[v].push_back(u);
    }
    void build(int root = 0){
        dfs(root, -1, 0, G);
        for(int i = 0; i < 25; i++){
            for(int j = 0; j < N; j++){
                if(parent[i][j] == -1) parent[i + 1][j] = -1;
                else parent[i + 1][j] = parent[i][parent[i][j]];
            }
        }
    }
    int lca(int v, int u){//lcaを求める
        if(depth[v] < depth[u]) swap(v, u);
        for(int k = 0; k < 25; k++){
            if((depth[v] - depth[u]) >> k & 1) v = parent[k][v];
        }
        if(v == u) return u;
        for(int k = 24; k >= 0; k--){
            if(parent[k][u] != parent[k][v]){
                u = parent[k][u];
                v = parent[k][v];
            }
        }
        return parent[0][u];
    }
private:
    void dfs(int v, int par, int d, vector<vector<int>>&G){
        parent[0][v] = par;
        depth[v] = d;
        for(int i: G[v]){
            if(i != par) dfs(i, v, d + 1, G);
        }
    }
};