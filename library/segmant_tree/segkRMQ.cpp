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
    int right_bin(int l, long long v) {
        l += n;
        long long zero = -1;
        do {
            while (l % 2 == 0) l >>= 1;
            if (dat[l] >= v) {
                while (l < n) {
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
        dat.resize(2 * n);
        for(int i = 0; i < 2 * n; i++) dat[i] = MAX;
    }
    void update(int k, int a){
        k += n;
        dat[k] = a;
        while(k > 0){
            k = k / 2;
            dat[k] = min(dat[k * 2], dat[k * 2 + 1]);
        }
    }
    long long query(int a, int b, int k, int l, int r){
        if(r <= a || b <= l) return MAX;
        if(a <= l && r <= b) return dat[k];
        else{
            long long vl = query(a, b, k * 2, l, (l + r) / 2);
            long long vr = query(a, b, k * 2 + 1, (l + r) / 2, r);
            return min(vl, vr);
        }
    }
};