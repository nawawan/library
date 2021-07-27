#include <iostream>
#include <vector>
using namespace std;
//今日連結成分分解を行う。
//orderが分解後のトポロジカル順序
//cntにそのトポロジカル順序のノードが格納されている
//O(N + M)
struct SCC{
    int N;
    vector<int> order;//分解後のトポロジカル順序(サイズ = 分解後のノード数)
    vector<vector<int>> cnt;
    SCC(int V){
        G.resize(V);
        rG.resize(V);
        N = V;
        order.resize(V);
    }
    void add(int s, int t){
        G[s].push_back(t);
        rG[t].push_back(s);
    }
    vector<vector<int>> build(){//分解後の頂点を返す
        used.resize(N, false);
        for(int i = 0; i < N; i++){
            if(!used[i]) dfs(i);
        }
        used.assign(N, false);  
        int k = 0;
        for(int i = (int)temp.size() - 1; i >= 0; i--){
            if(!used[temp[i]]) {
                rdfs(temp[i], k);
                k++;
            }
        }
        cnt.resize(k);
        for(int i = 0; i < N; i++){
            cnt[order[i]].push_back(i);
        }
        return cnt;
    }
private:
    vector<vector<int>> G, rG;
    vector<bool> used;
    vector<int> temp;
    void dfs(int s){
        used[s] = true;
        for(int j: G[s]){
            if(!used[j]) dfs(j);
        }
        temp.push_back(s);
    }
    void rdfs(int s, int k){
        used[s] = true;
        order[s] = k;
        for(int j: rG[s]){
            if(!used[j]) rdfs(j, k);
        }
    }
};