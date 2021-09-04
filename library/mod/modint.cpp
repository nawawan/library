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
    modint& operator/=(modint m){
        *this *= m.inv();
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
        x %= MOD;
        if(x < 0) x += MOD;
        return modint(x);
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
    bool operator==(const modint &m){
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
    bool operator!=(const modint &m){
        return modint(*this).val != m.val;
    }
    bool operator!=(const int &m){
        return modint(*this).val != m;
    }
};
const int MOD = 1000000007;
using mint = modint<MOD>;
const int MAX = 410000;
mint fac[MAX], finv[MAX], inv[MAX];
//MAX < MOD
void COMinit(){
    fac[0] = fac[1] = 1;
    finv[0] = finv[1] = 1;
    inv[1] = 1;
    for(int i = 2; i < MAX; i++){
        fac[i] = fac[i - 1] * i;
        inv[i] = mint(MOD) - inv[MOD % i] * (MOD / i);
        finv[i] = finv[i - 1] * inv[i];
    }
}
mint COM(int n, int k){
    if (n < k) return 0;
    if (n < 0 || k < 0) return 0;
    return fac[n] * finv[k] * finv[n - k];
}
mint nPm(int n, int m){
    if(n < m) return 0;
    if(n < 0 || m < 0) return 0;
    return fac[n] * finv[n - m];
}
mint repow(long long x, long long y){
    if(y == 0) return 1;
    mint res = 1;
    mint x2 = x;
    while(y > 0){
        if(y & 1) res = res * x2;
        x2 = x2 * x2;
        y >>= 1;
    }
    return res;
}