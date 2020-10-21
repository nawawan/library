#include <iostream>
#include <vector>
using namespace std;
//RANGE MAX QUERY
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
    int right_bin(int l, long long v) {//lから右のインデックスで、初めてのv以上の値のインデックスを返す
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
        return size - 1;
    }
    int left_bin(int r, long long v) {//rから左のインデックスで、初めてのv以下の値のインデックスを返す
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
                return r - n;
            }
        } while ((r & -r) != r);
        return size - 1;
    }
};
