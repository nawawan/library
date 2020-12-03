#include <bits/stdc++.h>
using namespace std;

int N, M;//Vは長天、Eは辺の数
struct UnionFind{//雛形を与える(初期化と結合のみ)
    vector<int> par;//親(根)
    vector<int> rank;//木の深さ

    UnionFind(int n) { init(n); } //まずはn個のノードを作る(この数は問題のNによって変わりうる)

    void init(int n){//初期化関数
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
        if(rank[x] < rank[y]) {
            par[x] = y;//深さが大きい方に小さい方を結合させる
            rank[y] += rank[x];
        }
        else{
            par[y] = x;
            rank[x] += rank[y];
        }
        //木に含まれる数を合わせる
    }

    int size(int x) {//深さを返す関数
        return rank[root(x)];
    }
};

struct edge{
    int from;
    int to;
    int cost;
};

bool comp(const edge &e1, const edge &e2){
    return e1.cost < e2.cost;
}

void kruskal(){
    vector<edge> G(M);
    sort(G.begin(), G.end(), comp);//小さいへんから選んでいく
    UnionFind U(N);
    int ans = 0;
    for(int i = 0; i < M; i++){
        edge e = G[i];
        if(!U.same(e.from, e.to)){//同じ木でない場合(閉路にならない場合)
            U.unite(e.from, e.to);
            ans += e.cost;
        }
    }
    cout << ans << endl;
}
