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
        INF = (1LL << 31) - 1;
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
    long long ju(long long l, long long r){
        return r != INF ? r : l;
    }
    void push(int k){
        if(lazy[k] == INF) return;
        if(k < n){
            lazy[2 * k] = ju(lazy[k * 2], lazy[k]);
            lazy[2 * k + 1] = ju(lazy[k * 2 + 1], lazy[k]);
        }
        dat[k] = ju(dat[k], lazy[k]);
        lazy[k] = INF;
    }
    void update(int k){//そのノードの更新
        dat[k] = min(ju(dat[k * 2], lazy[k * 2]), ju(dat[k * 2 + 1], lazy[k * 2 + 1]));
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
            l >>= 1;
            r >>= 1;
        }
        while(templ >>= 1, tempr >>= 1, templ){//上側のdatの更新
            if(lazy[templ] == INF) update(templ);
            if(lazy[tempr] == INF) update(tempr);
        }
    }
    long long find(int l, int r){
        long long res = INF;
        l += n;
        r += n - 1;
        for(int i = h; i > 0; i--){//まず上からの伝搬
            push(l >> i);
            push(r >> i);
        }
        r++;
        while(r > l){
            if(l & 1) {
                res = min(res, ju(dat[l], lazy[l]));
                l++;
            }
            if(r & 1) {
                r--;
                res = min(res, ju(dat[r], lazy[r]));
            }
            l >>= 1;
            r >>= 1;
        }
        return res;
    }
    int right_bin(int l, long long v) {
        if(l == size) return l;
        l += n;
        long long zero = -1;
        for(int i = h; i > 0; i--) push(l >> i);
        do {
            while (l % 2 == 0) l >>= 1;
            if (dat[l] >= v) {
                while (l < n) {
                    push(l);
                    l = (2 * l);
                    if (dat[l] < v) {
                        zero = max(zero, dat[l]);
                        l++;
                    }
                }
                return l - n;
            }
            zero = max(zero, dat[l]);
            l++;
        } while ((l & -l) != l);
        return size;
    }
    int left_bin(int r, long long v) {
        if(r == 0) return r;
        r += n;
        long long zero = -1;
        for(int i = h; i > 0; i--) push((r - 1) >> i);
        do {
            r--;
            while (r > 1 && (r % 2)) r >>= 1;
            if (dat[r] <= v) {
                while (r < n) {
                    push(r);
                    r = (2 * r + 1);
                    if (dat[r] > v) {
                        zero = max(zero, dat[r]);
                        r--;
                    }
                }
                return r + 1 - n;
            }
            zero = max(zero, dat[r]);
        } while ((r & -r) != r);
        return 0;
    }
};

//再帰実装(RMQ)
/*
struct lazysegK{
    int n;
    vector<long long> dat, lazy;
    long long MAX;
    lazysegK(int n_){
        n = 1;
        MAX = 1e18;
        while(n < n_) n *= 2;
        dat.resize(2 * n);
        lazy.resize(2 * n);
        for(int i = 0; i < 2 * n; i++) dat[i] = MAX;
    }
    void eval(int k, int l, int r){
        if(lazy[k] != MAX) dat[k] = min(dat[k], lazy[k]);
        if(r - l > 1){
            lazy[2 * k + 1] = min(lazy[2 * k + 1], lazy[k]);
            lazy[2 * k + 2] = min(lazy[2 * k + 2], lazy[k]);
        }
        lazy[k] = MAX;
    }
    void update(int a, int b, long long x, int k = 0, int l = 0, int r = -1){
        if(r < 0) r = n;
        eval(k, l, r);
        if(b <= l || r <= a) return;
        if(a <= l && r <= b){
            lazy[k] = x;
            eval(k, l, r);
        }
        else{
            update(a, b, x, 2 * k + 1, l, (l + r) / 2);
            update(a, b, x, 2 * k + 2, (l + r) / 2, r);
            dat[k] = min(dat[2 * k + 1], dat[2 * k + 2]);
        }
    }
    long long find(int a, int b, int k = 0, int l = 0, int r = -1){
        if(r < 0) r = n;
        if(r <= a || b <= l) return MAX;
        eval(k, l, r);
        if(a <= l && r <= b) return dat[k];
        else{
            long long vl = find(a, b, k * 2, l, (l + r) / 2);
            long long vr = find(a, b, k * 2 + 1, (l + r) / 2, r);
            return min(vl, vr);
        }
    }
};
*/