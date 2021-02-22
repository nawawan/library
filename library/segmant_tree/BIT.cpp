#include <iostream>
#include <vector>
#include <cassert>
using namespace std;
//1-indexed(累積和的な感じなので)
//sumをするときは1-indexedに注意
//queryは区間和[l, r]の
template<typename T>
struct BIT{
    vector<T> num;
    int N;
    BIT(int n){
        N = n + 1;
        num.resize(N, 0);
    }
    T sum(T t){
        long long res = 0;
        assert(t < N);
        while(t > 0){
            res += num.at(t);
            t -= t & -t;
        }
        return res;
    }
    void add(int ind, T t){
        ind++;
        assert(ind < N);
        while(ind < N){
            num[ind] += t;
            ind += ind & -ind;
        }
    }
    T query(int l, int r){
        return sum(r) - sum(l - 1);
    }
    int lower_bound(T k){//累積和がk以上となる最大のindexを返す
        int ind = 0;
        int beki = 1;
        assert(k >= 0);
        while(beki < N) beki <<= 1;
        for(int i = beki; i > 0; i >>= 1){
            if(ind + i < N && num[ind + i] < k){
                k -= num[ind + i];
                ind += i;
            }
        }
        return ind;
    }
};

/*
転倒数を求めるには
座圧して順にadd(index, 1);
sum(N) - sum(index + 1)を足す。
*/

//区間加算BIT
//add(l, r, x)で区間[l, r)にxを加算
//sumは1-indexedに注意

template<typename T>
struct BIT{
    vector<vector<T>> num(2);
    int N;
    BIT(int n){
        N = n + 1;
        num[0].resize(N);
        num[1].resize(N);
    }
    void add_sub(int t, int ind, T x){
        while(ind < N){
            num[t][ind] += x;
            ind += ind & (-ind);
        }
    }
    void add(int l, int r, T x){
        add_sub(0, l, -x * (l - 1));
        add_sub(0, r, x * (r - 1));
        add_sub(1, l, x);
        add_sub(1, r, -x);
    }
    T sum_sub(int t, int ind){
        T res = 0;
        while(ind > 0){
            res += num[t][ind];
            ind -= ind & (-ind);
        }
        return res;
    }
    T sum(int ind){
        return sum_sub(1, ind) * ind + sum_sub(0, ind);
    }
    T query(int l, int r){
        return sum(r) - sum(l - 1);
    }
};