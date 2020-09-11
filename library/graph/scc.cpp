#include <iostream>
#include <vector>
using namespace std;

struct scc{
    int N;
    vector<vector<int>> G, rG;
    vector<bool> used;
    vector<int> temp;
    vector<int> order;//分解後のトポロジカル順序
    vector<vector<int>> cnt;
    scc(int V){
        G.resize(V);
        rG.resize(V);
        N = V;
        order.resize(V);
    }
    void add(int s, int t){
        G[s].push_back(t);
        rG[t].push_back(s);
    }
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
    vector<vector<int>> solve(){//分解後の頂点数を返す
        used.resize(N, false);
        for(int i = 0; i < N; i++){
            if(!used[i]) dfs(i);
        }
        used.assign(N, false);  
        int k = 0;
        for(int i = (int)temp.size() - 1; i >= 0; i--){ //番号が大きい方から順にdfs
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
};