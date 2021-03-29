#include <vector>
using namespace std;
struct Euler_Tour{
    vector<int> order;
    vector<int> begin, end;
    Euler_Tour(vector<vector<int>> &G){
        int root = 0;
        int sz = G.size();
        begin.resize(sz);
        end.resize(sz);
        int ind = 0;
        dfs(root, ind, -1, G);
    }
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
    int size(){
        return order.size();
    }
};