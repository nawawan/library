#include <bits/stdc++.h>
using namespace std;

template<typename T>
bool is_prime(T n){//素数判定
    for(T i = 2; i * i <= n; i++){
        if(n % i == 0) return false;
    }
    return n != 1;
}

template<typename T>
vector<T> divisor(T n){//nの約数列挙
    vector<T> res;
    for(T i = 1; i * i <= n; i++){
        if(n % i == 0){
            res.push_back(i);
            if(i != n / i) res.push_back(n / i);
        }
    }
    return res;
}

template<typename T>
map<T, T> divide(T n){//素因数分解
    map<T, T> res;
    for(T i = 2; i * i <= n; i++){
        while(n % i == 0){
            res[i]++;
            n /= i;
        }
    }
    if(n != 1) res[n] = 1;
    return res;
}

//こっちが正式な高速素因数分解のコード(osa_k法)
vector<int> sieve(int n){
    vector<int> res(n, 0);
    iota(res.begin(), res.end(), 0);
    for(int i = 2; i < n; i++){
        if(res[i] < i) continue;
        for(int j = i * 2; j < n; j += i){
            res[j] = i;
        }
    }
    return res;
}
//sieveで求まった配列を用いて素因数分解0(logn)
vector<int> factor(int n, vector<int> &f){
    vector<int> t;
    while(n > 1){
        t.push_back(f[n]);
        n /= f[n];
    }
    return t;
}
