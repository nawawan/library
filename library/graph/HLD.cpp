#include<iostream>
#include <vector>
using namespace std;
//Heavy-Light Decompositon
//構築, O(N + M)
//hldは分解後の配列、preは変換前のノード番号
//nexidxは変換後の番号、nexは最も重い子ノード番号
//highestはその連結成分における最も浅いノード
struct HLD{
    vector<int> hld, depth, sz, pre, nex, par, nexidx, highest;
    vector<vector<int>> G;
    int N;
    HLD(int n) : N(n), depth(n), sz(n), pre(n), nex(n, -1), par(n), nexidx(n), highest(n), G(n){}
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
            if(depth[highest[u]] <= depth[highest[v]]){
                v = par[highest[v]];
            }
            else{
                u = par[highest[u]];
            }
        }
        if(depth[v] <= depth[u]) return v;
        else return u;
    }
    //パスが被覆する連結成分の始点と終点を返す(O(log(N)))
    //LCAを求めていく感じ
    //firstがhldにおいて小さいindexとなるように
    vector<pair<int, int>> query(int u, int v){
        vector<pair<int, int>> ret;
        while(highest[u] != highest[v]){
            if(depth[highest[u]] <= depth[highest[v]]){
                ret.push_back({nexidx[highest[u]], nexidx[u]});
                v = par[highest[v]];
            }
            else{
                ret.push_back({nexidx[highest[v]], nexidx[v]});
                u = par[highest[u]];
            }
        }
        ret.push_back({min(nexidx[v], nexidx[u]), max(nexidx[v], nexidx[v])});
        return ret;
    }
private:
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