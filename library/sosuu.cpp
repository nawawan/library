#include <bits/stdc++.h>
using namespace std;

bool is_prime(long long n){//素数判定
    for(long long i = 2; i * i <= n; i++){
        if(n % i == 0) return false;
    }
    return n != 1;
}

vector<long long> divisor(long long n){//nの約数列挙
    vector<long long> res;
    for(long long i = 1; i * i <= n; i++){
        if(n % i == 0){
            res.push_back(i);
            if(i != n / i) res.push_back(n / i);
        }
    }
    return res;
}

map<long long, long long> divide(long long n){//素因数分解
    map<long long, long long> res;
    for(long long i = 2; i * i <= n; i++){
        while(n % i == 0){
            res[i]++;
            n /= i;
        }
    }
    if(n != 1) res[n] = 1;
    return res;
}

vector<int> div(int n){//高速素因数分解用の配列(n ~ 10^6ならOK)
    vector<int> d(n + 1, 1);
    for(int i = 2; i <= n; i++){
        if(d[i] != 1) continue;
        int t = i;
        while(t <= n){
            d[t] = i;
            t += i;
        }
    }
    return d;
}
//こっちが正式な高速素因数分解のコード(kitamasa法)
vector<int> sieve(int n){
    vector<int> res(n, 0);
    iota(res.begin(), res.end(), 0);
    for(int i = 2; i * i < n; i++){
        if(res[i] < i) continue;
        for(int j = i * i; j < n; j += i){
            if(res[j] == j) res[j] = i;
        }
    }
    return res;
}
//sieveで求まった配列を用いて素因数分解0(logn)
vector<int> factor(int n, vector<int> &min_fac){
    vector<int> t;
    while(n > 1){
        t.push_back(min_fac[n]);
        n /= min_fac[n];
    }
    return t;
}