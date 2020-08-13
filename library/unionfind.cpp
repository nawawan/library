#include <bits/stdc++.h>
using namespace std;

struct UnionFind{
    vector<int> par;//親(根)
    vector<int> rank;//木の深さ

    //UnionFind(int n) { init(n); };
    UnionFind(int n){//初期化関数
        par.resize(n);
        rank.resize(n);
        for(int i = 0; i < n; i++){
            par[i] = i;//初めはノード一個の木なので根は自身
            rank[i] = 1;
        }
    }

    int root(int x){//木の根を求める
    if(par[x] == x) return x;
    else return par[x] = root(par[x]);
    }

    bool same(int x, int y){//同じ木かどうか判定
        return root(x) == root(y);//同じ木ならtrue
    }

    void unite(int x, int y){
        x = root(x);
        y = root(y);
        if(x == y) return;//もし同じ木に属していたら何もしない
        if(rank[x] < rank[y]) swap(x, y);//数が大きい方に小さい方を結合させる
        par[y] = x;
        rank[x] += rank[y];//深さが同じ時だけ結合後深さが増える
    }

    int size(int x) {//深さを返す関数
        return rank[root(x)];
    }
};