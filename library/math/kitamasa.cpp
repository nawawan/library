#include <iostream>
#include <vector>
using namespace std;
//きたまさ法
//k^2log(N)でa_N番目(任意)の係数を求める
// a_N = d * aとなる
//行列累乗の高速化
template<typename T>
struct kitamasa{
    vector<T> a;//初期値
    vector<T> d;//係数用
    int k;
    kitamasa(vector<T>&a, vector<T>&d) : a(a), d(d), k((int)a.size()){}

    vector<T> build(long long n){
        if(n == k) return d;
        vector<T> res(k);
        vector<bool> ope;
        while(n > k){
            if((n & 1) || n < 2 * k){
                ope.push_back(true);
                n -= 1;
            }
            else{
                ope.push_back(false);
                n >>= 1;
            }
        }
        int sz = ope.size();
        vector<T> ret = d;
        vector<T> t(k);
        vector<vector<T>> t2(k, vector<T>(k));
        for(int s = sz - 1; s >= 0; --s){
            if(ope[s]){
                copy(ret.begin(), ret.end(), t.begin());
                for(int j = 0; j < k; ++j) ret[j] = d[j] * t[k - 1];
                for(int j = 0; j < k - 1; ++j) ret[j + 1] += t[j]; 
            }
            else{
                copy(ret.begin(), ret.end(), t2[0].begin());
                for(int i = 0; i < k - 1; ++i){
                    t2[i + 1].assign(k, 0);
                    for(int j = 0; j < k; ++j) t2[i + 1][j] += d[j] * t2[i][k - 1];
                    for(int j = 0; j < k - 1; ++j) t2[i + 1][j + 1] += t2[i][j];
                }
                ret.assign(k, 0);
                for(int i = 0; i < k; ++i){
                    for(int j = 0; j < k; ++j){
                        ret[j] += t2[0][i] * t2[i][j];
                    }
                }
            }
        }
        return ret;
    }

    T calc(long long n){
        if(n < k) return a[n];
        vector<T> res = build(n);
        T ret = 0;
        for(int i = 0 ; i < k; ++i){
            ret += a[i] * res[i];
        }
        return ret;
    }
};