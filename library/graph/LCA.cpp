#include <vector>
using namespace std;
struct LCA{
    vector<vector<long long>> parent;
    vector<int> depth;
    void dfs(int v, int par, int d, vector<vector<int>>&G){
        parent[0][v] = par;
        depth[v] = d;
        for(int i: G[v]){
            if(i != par) dfs(i, v, d + 1, G);
        }
    }
    LCA(int N, int root, vector<vector<int>> &G){
        depth.resize(N);
        parent.resize(41, vector<long long> (N));
        dfs(root, -1, 0, G);
        for(int i = 0; i < 40; i++){
            for(int j = 0; j < N; j++){
                if(parent[i][j] == -1) parent[i + 1][j] = -1;
                else parent[i + 1][j] = parent[i][parent[i][j]];
            }
        }
    }
    int lca(int v, int u){//lcaを求める
        if(depth[v] < depth[u]) swap(v, u);
        for(int k = 0; k < 41; k++){
            if((depth[v] - depth[u]) >> k & 1) v = parent[k][v];
        }
        if(v == u) return u;
        for(int k = 40; k >= 0; k--){
            if(parent[k][u] != parent[k][v]){
                u = parent[k][u];
                v = parent[k][v];
            }
        }
        return parent[0][u];
    }
};