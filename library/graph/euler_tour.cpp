#include <vector>
using namespace std;
struct Euler_Tour{
    Euler_Tour(vector<vector<int>> &g): begin(g.size()), end(g.size()), G(g){}
    Euler_Tour(int N) : begin(N), end(N), G(N) {}
    void add_edge(int u, int v){
        G[u].push_back(v);
        G[v].push_back(u);
    }
    void build(int root = 0){
        int ind = 0;
        dfs(root, ind, -1, G);
    }
    pair<int, int> get(int node){
        return make_pair(begin[node], end[node]);
    }
    vector<int> get_order(){
        return order;
    }
private:
    vector<int> order;
    vector<int> begin, end;
    vector<vector<int>> G;
    void dfs(int now, int &ind, int par, vector<vector<int>>&G){
        order.push_back(now);
        begin[now] = ind;
        ++ind;
        for(int e: G[now]){
            if(e != par){
                dfs(e, ind, now, G);
                order.push_back(now);
                ++ind;
            }
        }
        end[now] = ind;
    }
};