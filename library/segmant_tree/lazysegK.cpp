#include <iostream>
#include <vector>
#include <cmath>
using namespace std;
long long MAX = 1e18;
//区間和
struct lazysegK{//非再帰
    int n, h;
    long long INF;
    int size;
    vector<long long> dat, lazy;
    lazysegK(int n_){
        n = 1;
        INF = 1e18;
        size = n_;
        h = ceil(log2(n_));
        while(n < n_) n *= 2;
        dat.resize(2 * n);
        lazy.resize(2 * n);
        for(int i = 1; i < 2 * n; i++) {
            dat[i] = INF;
            lazy[i] = INF;
        }
    }
private:
    void push(int k){
        if(lazy[k] == INF) return;
        if(k < n){
            lazy[2 * k] = lazy[k];
            lazy[2 * k + 1] = lazy[k];
        }
        dat[k] = lazy[k];
        lazy[k] = INF;
    }
    void update(int k){//そのノードの更新
        dat[k] = min(lazy[k * 2], lazy[k * 2 + 1]);
    }
public:
    void update(int l, int r, long long a){//l, r区間にaを作用
        l += n;
        r += n - 1;
        for(int i = h; i > 0; i--){//上からの伝搬
            push(l >> i);
            push(r >> i);
        }
        int templ = l, tempr = r;
        r++;
        while(l < r){//区間にaを作用
            if(l & 1) lazy[l++] = a;
            if(r & 1) lazy[--r] = a;
        }
        while(templ >>= 1, tempr >>= 1, templ){//上側のdatの更新
            if(lazy[templ] == INF) update(templ);
            if(lazy[tempr] == INF) update(tempr);
        }
    }
    long long query(int l, int r){
        long long res = 0;
        l += n;
        r += n - 1;
        for(int i = h; h > 0; h--){//まず上からの伝搬
            push(l >> i);
            push(r >> i);
        }
        while(r > l){
            if(l & 1) {
                push(l);
                res = max(res, dat[l++]);
            }
            if(r & 1) {
                r--;
                push(r);
                res = max(res, dat[r]);
            }
            l >>= 1;
            r >>= 1;
        }
        return res;
    }
};
