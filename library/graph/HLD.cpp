#include<iostream>
#include <vector>
using namespace std;
//Heavy-Light Decompositon
//構築, O(N + M)
//hldは分解後の配列、preは変換前のノード番号
//nexidxは変換後の番号、nexは最も重い子ノード番号
//highestはその連結成分における最も浅いノード
struct HLD{
    HLD(int n) : N(n), depth(n), sz(n), pre(n), par(n), highest(n), G(n){
        nex.resize(n, -1);
        nexidx.resize(n, -1);
    }
    HLD(vector<vector<int>> &G) : N(G.size()), G(G){
        depth.resize(N);
        sz.resize(N);
        pre.resize(N);
        nex.resize(N, -1);
        nexidx.resize(N, -1);
        par.resize(N);
        highest.resize(N);
    }
    void add_edge(int s, int t){
        G[s].push_back(t);
        G[t].push_back(s);
    }
    void build(int root = 0){
        dfs_calsz(root, -1);
        dfs_makehld(root, -1, root);
    }
    //O(log(N))
    int lca(int u, int v){
        while(highest[u] != highest[v]){
            if(depth[highest[u]] > depth[highest[v]]) swap(u, v);
            v = par[highest[v]];
        }
        if(nexidx[u] > nexidx[v]) swap(u, v);
        return u;
    }
    //パスが被覆する連結成分の始点と終点を返す(O(log(N)))
    //LCAを求めていく感じ
    //firstがhldにおいて小さいindexとなるように
    vector<pair<int, int>> query(int u, int v){
        vector<pair<int, int>> ret;
        while(highest[u] != highest[v]){
            if(depth[highest[u]] <= depth[highest[v]]){
                ret.push_back({nexidx[highest[v]], nexidx[v]});
                v = par[highest[v]];
            }
            else{
                ret.push_back({nexidx[highest[u]], nexidx[u]});
                u = par[highest[u]];
            }
        }
        ret.push_back({min(nexidx[v], nexidx[u]), max(nexidx[v], nexidx[u])});
        return ret;
    }
    //元のindex -> HLD上のindex
    int next_id(int x){
        return nexidx[x];
    }
    //HLD上のindex -> 元のindex
    int pre_id(int x){
        return pre[x];
    }
    //頂点の深さを返す
    int dep(int x){
        return depth[x];
    }
    vector<int> hld, depth, sz, pre, nex, par, nexidx, highest;
private:
    vector<vector<int>> G;
    int N;
    int dfs_calsz(int now, int parent = -1){
        sz[now] = 1;
        par[now] = parent;
        if(parent != -1) depth[now] = depth[parent] + 1;
        int ma = 0;
        for(int t: G[now]){
            if(t == parent) continue;
            int temp = dfs_calsz(t, now);
            sz[now] += temp;
            if(temp > ma){
                nex[now] = t;
                ma = temp;
            }
        }
        return sz[now];
    }
    void dfs_makehld(int now, int par, int high){
        nexidx[now] = hld.size();
        pre[hld.size()] = now;
        highest[now] = high;
        hld.push_back(now);
        if(nex[now] != -1) dfs_makehld(nex[now], now, high);
        for(int t: G[now]){
            if(t != par && t != nex[now]) dfs_makehld(t, now, t);
        }
    }
};