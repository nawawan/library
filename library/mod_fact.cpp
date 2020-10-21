#include <iostream>
#include <vector>
using namespace std;
//これはpが素数ではない場合にも適用できる
const int MAX = 1e5;
long long extgcd(long long a, long long b, long long &x, long long &y){
    long long d = a;
    if(b != 0){
        d = extgcd(b, a % b, y, x);
        y -= (a / b) * x;
    }
    else{
        x = 1;
        y = 0;
    }
    return d;
}
long long mod_inverse(long long a, long long m){
    long long x, y;
    extgcd(a, m, x, y);
    return (m + x % m) % m;
}
struct mod_com{//n!のmod pを返す(どちらかというとnCkのための前処理)
    vector<long long> fact;
    mod_com(long long p){//k < pに対してk!mod pのテーブルを作成
        fact.resize(MAX);//nに合わせてMAXを変更すれば良い
        for(int i = 0; i < MAX; i++){
            if(i == 0) fact[i] = 1;
            else fact[i] = fact[i - 1] * i % p;
        }
    }
    long long modf(int n, long long p, long long &e){//n! = a * p^eの時のa mod pを返す
        e = 0;
        if(n == 0) return 1;
        long long res = modf(n / p, p, e);
        e += n / p;
        //(p - 1)! = -1 mod pを利用(n/pが奇数の時はmodのとり方に注意)
        if(n / p % 2 != 0) return res * (p - fact[n % p]) % p;
        return res * fact[n % p] % p;
    }
    //nCk (mod p)を作成pは素数でなくてもいける
    long long COMB(long long n, long long k, long long p){
        if(n < 0 || k < 0 || n < k) return 0;
        long long e1, e2, e3;//e1 > e2 + e3ならpで割り切れる、割り切れない時はnCk = a1 * (a2 * a3)^-1(mod p)
        long long a1 = modf(n, p, e1), a2 = modf(k, p, e2), a3 = modf(n - k, p, e3);
        if(e1 > e2 + e3) return 0;
        return a1 * mod_inverse(a2 * a3 % p, p) % p;
    }
};