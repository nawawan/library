#include <iostream>
#include <vector>
#include <cassert>
using namespace std;
//抽象化セグメントツリー
/*
https://hcpc-hokudai.github.io/archive/structure_segtree_001.pdf
↑参考になりすぎ！
mergeは二つの子を指定した演算で結合
idはidentity、単位元のこと
*/
template<typename S, S (*merge)(S, S), S (*id)()> struct segtree{
    int n;
    int size;//元の配列の大きさ
    vector<S> dat;
    segment_tree(int n_) : n(n_ * 2), size(n_), dat(n, id()){}
    segment_tree(vector<S> &v){
        size = (int)v.size();
        n = size * 2;
        dat.resize(n, id());
        for(int i = 0; i < size; i++){
            update(i, v[i]);
        }
    }
    segtree& operator[](const int i){
        return dat[i + size];
    }
    void update(int ind, S a){
        ind += n;
        dat[ind] = a;
        while(ind > 1){
            ind >>= 1;
            dat[ind] = merge(dat[ind << 1 | 0], dat[ind << 1 | 1]);
        }
    }
    S query(int l, int r){
        if(l >= r) return id();
        S res = id();
        l += size;
        r += size;
        while(r > l){
            if(l & 1) res = merge(res, dat[l++]);
            if(r & 1) res = merge(dat[--r], res);
            l >>= 1;
            r >>= 1;
        }
        return res;
    }
};