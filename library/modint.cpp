#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>
using namespace std;
//まぁ基本MOD=10^9 + 7か998244353だし…
template<const int MOD> struct modint{
    long long val;
    modint(): val(0) {}
    modint(long long x){
        if(x < 0) val = x % MOD + MOD;
        else val = x % MOD;
    }
    modint(const modint &t){
        val = t.val;
    }
    modint& operator =(const modint m){
        val = m.val;
        return *this;
    }
    modint operator -(){
        return modint(-val);
    }
    modint& operator-=(const modint &m){
        val -= m.val;
        if(val < 0) val += MOD;
        return *this;
    }
    modint& operator+=(const modint &m){
        val += m.val;
        if(val >= MOD) val -= MOD;
        return *this;
    }
    modint& operator*=(const modint &m){
        val *= m.val;
        val %= MOD;
        return *this;
    }
    modint& operator/=(const modint &m){
        val *= m.inv();
        return *this;
    }
    modint inv(){
        long long x = 1, y = 0;
        long long a = val, b = MOD;
        while(b != 0){
            long long t = a / b;
            a -= t * b;
            x -= t * y;
            swap(a, b);
            swap(x, y);
        }
        val = x % MOD;
        if(val < 0) val += MOD;
        return modint(val);
    }
    modint pow(long long k){
        long long res = 1;
        long long v = val;
        while(k > 0){
            if(k & 1) res = res * v % MOD;
            v = v * v % MOD;
            k >>= 1;
        }
        return modint(res);
    }
    modint operator==(const modint &m){
        return val == m.val;
    }
    modint operator+(const modint &m){
        return modint(*this) += m;
    }
    modint operator-(const modint &m){
        return modint(*this) -= m;
    }
    modint operator*(const modint &m){
        return modint(*this) *= m;
    }
    modint operator/(const modint &m){
        return modint(*this) /= m;
    }
};