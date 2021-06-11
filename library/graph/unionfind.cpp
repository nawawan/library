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

//部分永続UnionFind
struct UnionFind{
    vector<int> rank;
    vector<int> par;
    vector<int> time;
    int now;//現在時刻
    int INF = 1000000000;
    UnionFind(int N) : par(N), now(0){
        rank.resize(N, 1);
        time.resize(N, INF);
        for(int i = 0; i < N; i++) par[i] = i;
    }
    //O(logn)
    int root(int t, int x){
        if(time[x] > t) return x;
        else return root(t, par[x]);
    }

    bool same(int x, int y){
        return root(now, x) == root(now, y);
    }

    int find_time(int a, int b){
        if(a == INF || b == INF) return -1;
        if(a == b) return 0;
        else if(time[a] < time[b]){
            if(par[a] == b) return time[a];
            a = par[a];
            return find_time(a, b);
        }
        else{
            if(par[b] == a) return time[b];
            b = par[b];
            return find_time(a, b);
        }
    }

    void unite(int x, int y){
        ++now;
        x = root(now, x);
        y = root(now, y);
        if(x == y) return;
        if(rank[x] < rank[y]) swap(x, y);
        par[y] = x;
        rank[x] += rank[y];
        time[y] = now;
    }

    int size(int x) {
        return rank[root(now, x)];
    }
};