#include <bits/stdc++.h>
using namespace std;
long long MOD = 1e9 + 7;
long long repow(long long x, long long n){//x^nのmodのmodを計算する
    if(n == 0) return 1;
    if(n % 2 == 0){
        long long t = repow(x, n / 2); //nが偶数のときはx^n = x^(n / 2) * x^(n / 2)
        return t * t % MOD;
    } 
    return x * repow(x, n - 1) % MOD;//nが奇数のときはx^n = x * x^(n - 1)
}

long long repow(long long x, long long y, int MOD){
    if(x == 0) return 0;
    if(y == 0) return 1;
    x %= MOD;
    long long res = 1;
    while(y != 0){
        if(y & 1) res = res*x%MOD;
        x = x * x % MOD;
        y >>= 1;
    }
    return res;
}