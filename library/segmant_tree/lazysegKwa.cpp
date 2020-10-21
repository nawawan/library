#include <iostream>
#include <vector>
using namespace std;
//再帰、区間和
struct lazysegK{
    int n;
    vector<long long> dat, lazy;
    long long MAX;
    lazysegK(vector<long long> v){
        int n_ = (int) v.size();
        n = 1;
        MAX = 1e18;
        while(n < n_) n *= 2;
        dat.resize(2 * n);
        lazy.resize(2 * n);
        for(int i = 0; i < n_; i++) {
            dat[i + n] = v[i]; 
        }
        for(int i = n - 2; i >= 0; i--){
            dat[i] = dat[i * 2 + 1] + dat[i * 2 + 2];
        }
    }
    void eval(int k, int l, int r){
        if(lazy[k] != 0){
            dat[k] += lazy[k];
            if(r - l > 1){
                lazy[2 * k + 1] += lazy[k] / 2;
                lazy[2 * k + 2] += lazy[k] / 2;
            }
            lazy[k] = 0;
        }
    }
    void update(int a, int b, long long x, int k = 0, int l = 0, int r = -1){
        if(r < 0) r = n;
        eval(k, l, r);
        if(b <= l || r <= a) return;
        if(a <= l && r <= b){
            lazy[k] += (r - l) * x;
            eval(k, l, r);
        }
        else{
            update(a, b, x, 2 * k + 1, l, (l + r) / 2);
            update(a, b, x, 2 * k + 2, (l + r) / 2, r);
            dat[k] = dat[2 * k + 1] + dat[2 * k + 2];
        }
    }
    long long find(int a, int b, int k = 0, int l = 0, int r = -1){
        if(r < 0) r = n;
        if(r <= a || b <= l) return 0;
        eval(k, l, r);
        if(a <= l && r <= b) return dat[k];
        else{
            long long vl = find(a, b, k * 2, l, (l + r) / 2);
            long long vr = find(a, b, k * 2 + 1, (l + r) / 2, r);
            return vl + vr;
        }
    }
};