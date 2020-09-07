#include <iostream>
#include <vector>
using namespace std;
long long MAX = 1e18;
//区間和
struct latesegK{
    long long n;
    vector<long long> dat, lazy;
    //これはRMQ用
    latesegK(long long n_){
        n = 1;
        while(n < n_) n *= 2;
        dat.resize(2 * n - 1);
        lazy.resize(2 * n - 1, 0);
        for(int i = 0; i < 2 * n - 1; i++) {
            dat[i] = MAX;
        }
    }
    void update(long long k, long long a){
        k += n - 1;
        dat[k] = a;
        while(k > 0){
            k = (k - 1) / 2;
            dat[k] = dat[k * 2 + 1] + dat[k * 2 + 2];
        }
    }
    long long query(long long a, long long b, long long k, long long l, long long r){
        if(r <= a || b <= l) return MAX;
        if(a <= l && r <= b) return dat[k];
        else{
            long long vl = query(a, b, k * 2 + 1, l, (l + r) / 2);
            long long vr = query(a, b, k * 2 + 2, (l + r) / 2, r);
            return min(vl, vr);
        }
    }
};