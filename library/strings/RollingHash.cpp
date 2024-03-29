#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
struct RollingHash{
    static const ull MOD = (1ULL << 61) - 1;
    static const ull MASK30 = (1ULL << 30) - 1;
    static const ull MASK31 = (1ULL << 31) - 1;
    const ull base;
    static const ull POSITIVIZER = MOD * 4;
    vector<ull> power_base;
    RollingHash(ull b = rand_base()) : base(b), power_base({1}){};
    static ull Mul(ull a, ull b){//Modを計算しない
        ull au = a >> 31;
        ull al = a & MASK31;
        ull bu = b >> 31;
        ull bl = b & MASK31;
        ull res = au * bu * 2 + bl * al;
        ull mid = au * bl + al * bu;
        ull midu = mid >> 30;
        ull midl = mid & MASK30;
        res += (midl << 31) + midu;
        return res;
    }
    static ull CalMod(ull x){
        ull xu = x >> 61;
        ull xl = x & MOD;
        ull res = xl + xu;
        if(res >= MOD) res -= MOD;
        return res;
    }
    static ull rand_base(){
        random_device seed_gen;
        mt19937_64 rand(seed_gen());
        return (rand() & MOD);
    }
    void expand(int sz){
        if((int)power_base.size() < sz + 1){
            int pre_sz = power_base.size();
            power_base.resize(sz + 1);
            for(int i = pre_sz - 1; i < sz; i++){
                power_base[i + 1] = CalMod(Mul(power_base[i], base));
            }
        }
    }
    //S[num...|S|) + S[0..num)のハッシュ値を返す
    //n = |S|
    ull shift(vector<ull> &hash, int num, int n){
        ull temp = CalMod(POSITIVIZER + hash.back() - Mul(hash[num], power_base[n - num]));
        return CalMod(Mul(temp, power_base[num]) + hash[num]);
    }
    vector<ull> makehash(string &S){
        int sz = (int)S.size();
        vector<ull> hash(sz + 1);
        for(int i = 0; i < sz; i++){
            hash[i + 1] = CalMod(Mul(hash[i], base) + S[i]);
        }
        return hash;
    }
    template<typename T>
    vector<ull> makehash(vector<T> &V){
        int sz = (int)V.size();
        vector<ull> hash(sz + 1);
        for(int i = 0; i < sz; i++){
            hash[i + 1] = CalMod(Mul(hash[i], base) + V[i]);
        }
        return hash;
    }
    //文字列(または配列)のS[l,...,r)部分のハッシュ値を返す(r > l)
    ull query(vector<ull> &hash, int l, int r){
        assert(r > l);
        expand(r - l);
        ull h = CalMod(POSITIVIZER + hash[r] - Mul(hash[l], power_base[r - l]));
        return h;
    }
    //hashがaのもののS[l1,...,r1]とbのもののS[l2,...,r2)が先頭からどれだけ一致しているかを返す(一致している文字数)
    int LCP(vector<ull>&a, int l1, int r1, vector<ull>&b, int l2, int r2){
        int len = min(r1 - l1, r2 - l2);
        int lb = 0, ub = len + 1;
        while(ub - lb > 1){
            int mid = (ub + lb) / 2;
            if(query(a, l1, l1 + mid) == query(b, l2, l2 + mid)) lb = mid;
            else ub = mid;
        }
        return lb;
    }
};