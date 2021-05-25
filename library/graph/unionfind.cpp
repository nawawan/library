#include <bits/stdc++.h>
using namespace std;

struct UnionFind{
    vector<int> par;
    vector<int> rank;

    UnionFind(int n){
        par.resize(n);
        rank.resize(n);
        for(int i = 0; i < n; i++){
            par[i] = i;
            rank[i] = 1;
        }
    }

    int root(int x){
    if(par[x] == x) return x;
    else return par[x] = root(par[x]);
    }

    bool same(int x, int y){
        return root(x) == root(y);
    }

    void unite(int x, int y){
        x = root(x);
        y = root(y);
        if(x == y) return;
        if(rank[x] < rank[y]) swap(x, y);
        par[y] = x;
        rank[x] += rank[y];
    }

    int size(int x) {
        return rank[root(x)];
    }
};