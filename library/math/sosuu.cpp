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

//こっちが正式な高速素因数分解のコード(osa_k法)
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

//注意!!(雑魚すぎてn <= 10^9)での動作しか保証できません
/*
//mirror-labinの素数判定法と高速素因数分解(ロー法)(O(n^1/4))
long long repow(long long x, long long y, long long M){
    if(y == 0) return 1;
    long long res = 1;
    while(y != 0){
        if(y & 1) res = res * x % M;
        x = x * x % M;
        y >>= 1;
    }
    return res;
}
bool MRprime(long long p){
    if(p == 2) return true;
    if(p == 1 || p % 2 == 1) return false;
    long long d = p - 1;
    d = d / (d & -d);//最上位ビットでわる(dは奇数になる)
    vector<long long> a = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};//2^64までならこれで十分
    for(int i = 0; i < (int)a.size(); i++){
        long long t = repow(a[i], d, p);
        long long tmpd = d;
        if(t == 1) continue;
        while(t != p - 1){
            t = (t * t) % p;
            if(t == 1 || tmpd == n - 1) return false;//-1が出る前に1が出たり、指数がn-1になったら合成数
            tmpd <<= 1;
        }
    }
    return true;
}
//こっちがロー法
struct Rho{
    mt19937 mt;
    long long c:
    Rho(){
        mt.seed(clock());
    }
    long long f(long long x, long long p){
        return (x * x + c) % p;
    }
    long long repow(long long x, long long y){
        if(y == 0) return 1;
        long long res = 1;
        while(y != 0){
            if(y & 1) res = res*x%MOD;
            x = x * x % MOD;
            y >>= 1;
        }
        return res;
    }
    bool MRprime(long long p){
        if(p == 2) return true;
        if(p == 1 || p % 2 == 1) return false;
        long long d = p - 1;
        d = d / (d & -d);//最上位ビットでわる(dは奇数になる)
        vector<long long> a = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};//2^64までならこれで十分
        if(p <= (1LL << 30)) a = {2, 7, 61};
        for(int i = 0; i < (int)a.size(); i++){
            long long t = repow(a[i], d, p);
            long long tmpd = d;
            if(t == 1) continue;
            while(t != p - 1){
                t = (t * t) % p;
                if(t == 1 || tmpd == n - 1) return false;//-1が出る前に1が出たり、指数がn-1になったら合成数
                tmpd <<= 1;
            }
        }
        return true;
    }
    long long check(long long n){//約数を一つ見つける
        long long x = mt % n;
        long long y = x;
        c = mt % n;
        long long g = 1;
        while(g == 1){
            x = f(x, n);
            y = f(f(y, n), n);
            g = gcd(abs(x - y), n);
        }
        if(g == n){//約数が見つからなかった時は再走
            return -1;
        }
        return g;
    }
    vector<long long> factors(long long n){//繰り返して素因数分解
        if(n <= 1) return {};
        if(MRprime(n)) return {n};
        long long fac = -1;
        while(fac == -1){
            fac = check(n);
        }
        vector<long long> zen = factors(fac);
        vector<long long> kou = factors(n / fac);
        zen.insert(zen.end(), kou.begin(), kou.end());
        return zen;
    }
};
*/
