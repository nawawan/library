#include <iostream>
#include <vector>
using namespace std;
//区間和を書いてます
struct segK{//非再帰
    int n;
    long long MIN;
    int size;
    vector<long long> dat;
    segK(int n_){
        n = 1;
        MIN = -1;
        size = n_;
        while(n < n_) n *= 2;
        dat.resize(2 * n);
        for(int i = 1; i < 2 * n; i++) dat[i] = MIN;
    }
    void update(int k, long long a){
        k += n;
        dat[k] = a;
        while(k > 0){
            k >>= 1;
            dat[k] = max(dat[k << 1 | 0], dat[k << 1 | 1]);
        }
    }
    long long query(int l, int r){
        long long res = 0;
        l += n;
        r += n;
        while(r > l){
            if(l & 1) res = max(res, dat[l++]);
            if(r & 1) res = max(res, dat[--r]);
            l >>= 1;
            r >>= 1;
        }
        return res;
    }
    //区間[l, r]で、値がv以下となる最小のrを返す
    int right_bin(int l, long long v) {
        if(l == size) return l;
        l += n;
        do {
            while (l % 2 == 0) l >>= 1;
            if (dat[l] >= v) {
                while (l < n) {
                    l = (2 * l);
                    if (dat[l] < v) {
                        l++;
                    }
                }
                return l - n;
            }
            l++;
        } while ((l & -l) != l);
        return size;
    }
    //区間[l, r]で値がv以下となる最大のlを返す
    int left_bin(int r, long long v) {
        if(r == 0) return r;
        r += n;
        do {
            r--;
            while (r > 1 && (r % 2)) r >>= 1;
            if (dat[r] <= v) {
                while (r < n) {
                    r = (2 * r + 1);
                    if (dat[r] > v) {
                        r--;
                    }
                }
                return r + 1 - n;
            }
        } while ((r & -r) != r);
        return 0;
    }
    //上から二分探索
    int bin(long long v, int now = 1){
        while(now < n){
            if(dat[now << 1] >= v) now <<= 1;
            else{
                v -= dat[now << 1];
                now = (now << 1) | 1;
            }
        }
        return now - n;
    }
    long long get(int ind){
        return dat[ind + n];
    }
};



//再帰バージョンRMQ
struct segK{
    int n;
    vector<long long> dat;
    long long MAX;
    segK(int n_){
        n = 1;
        MAX = 1e18;
        while(n < n_) n *= 2;
        dat.resize(2 * n - 1);
        for(int i = 0; i < 2 * n - 1; i++) dat[i] = MAX;
    }
    void update(int k, int a){
        k += n - 1;
        dat[k] = a;
        while(k > 0){
            k = (k - 1) / 2;
            dat[k] = min(dat[k * 2 + 1], dat[k * 2 + 2]);
        }
    }
    long long query(int a, int b, int k, int l, int r){
        if(r <= a || b <= l) return MAX;
        if(a <= l && r <= b) return dat[k];
        else{
            long long vl = query(a, b, k * 2 + 1, l, (l + r) / 2);
            long long vr = query(a, b, k * 2 + 2, (l + r) / 2, r);
            return min(vl, vr);
        }
    }
};

//区間和セグ木(転倒数を求めるためのやつもあり)
struct segK{//非再帰
    int n;
    long long MIN;
    int size;
    vector<long long> dat;
    segK(int n_){
        n = 1;
        MIN = 0;
        size = n_;
        while(n < n_) n *= 2;
        dat.resize(2 * n);
        for(int i = 1; i < 2 * n; i++) dat[i] = MIN;
    }
    void update(int k, long long a){
        k += n;
        dat[k] = a;
        while(k > 0){
            k >>= 1;
            dat[k] = dat[k << 1 | 0] + dat[k << 1 | 1];
        }
    }
    long long query(int l, int r){
        long long res = 0;
        l += n;
        r += n;
        while(r > l){
            if(l & 1) res += dat[l++];
            if(r & 1) res += dat[--r];
            l >>= 1;
            r >>= 1;
        }
        return res;
    }
    long long inv_bin(int r) {//vより小さくて、r以下で最も大きいインデックスを返す
        if(r == 0) return r;
        long long res = 0;
        r += n;
        do {
            r--;
            while (r > 1 && (r % 2)) r >>= 1;
            res += dat[r];
        } while ((r & -r) != r);
        return res;
    }
};