#include <iostream>
#include <vector>
using namespace std;
struct twosat{
    int N, n;
    vector<vector<int>> G, rG;
    vector<bool> used;
    vector<int> temp;
    vector<int> order;//分解後のトポロジカル順序
    vector<bool> judge;//復元用
    twosat(int V){
        G.resize(2 * V);
        rG.resize(2 * V);
        N = 2 * V;
        n = V;
        order.resize(2 * V);
        judge.resize(V);
    }
    void add_edge(int s, int t){
        G[s].push_back(t);
        rG[t].push_back(s);
    }
    void add(int s, bool f, int t, bool g){
        add_edge(s + (f ? n : 0), t + (g ? 0 : n));
        add_edge(t + (g ? n : 0), s + (f ? 0 : n));
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
    bool build(){
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
        for(int i = 0; i < n; i++){
            if(order[i] > order[i + n]) judge[i] = true;
            else if(order[i] < order[i + n]) judge[i] = false;
            else return false;
        }
        return true;
    }
};