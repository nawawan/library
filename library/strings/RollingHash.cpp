#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <random>
#include <cassert>
using namespace std;
typedef unsigned long long ull;
const ull base = 1e9 + 7;//除数は2^64と考える
//オーバーフロー = 「MODをとること」となっている
/*カス、衝突します
https://www.slideshare.net/nagisaeto/rolling-hash-149990902
を参照してください(2^64は普通にやばい)
bool rolliha(string S, string T){//TがSに含まれているかどうか
    int slen = S.size(), tlen = T.size();
    if(slen < tlen) return false;
    ull bt = 1;
    for(int i = 0; i < tlen; i++) bt *= base;
    ull sb = 0, tb = 0;//先頭tlen文字のハッシュ値
    for(int i = 0; i < tlen; i++) sb = sb * base + (ull) S[i];
    for(int i = 0; i < tlen; i++) tb = tb * base + (ull) T[i];
    //Sの長さtlenの部分文字列がTに一致するか判定
    for(int i = 0; i + tlen <= slen; i++){
        if(sb == tb) return true;
        if(i + tlen < slen) sb = sb * base - bt * (ull)S[i] + (ull)S[i + tlen];
    }
    return false;
}


int overlap(string S, string T){//Sの末尾、Tの先頭が何個一致するか
    int slen = S.size(), tlen = T.size();
    int ans = 0;
    ull sb = 0, tb = 0, bt = 1;
    for(int i = 0; i < min(slen, tlen); i++){
        sb = sb + bt * (ull) S[slen - i - 1];
        tb = tb + tb * (ull) T[i];
        bt *= base;
        if(sb == tb) ans++;
    }
    return ans;
}

//(使わないだろうけど、長さがk(<= S.size())で固定された文字列がSに含まれているかどうか判定する構造体)
struct rolliha{
    const ull base = 1e9 + 7;
    map<ull, int> m;
    ull bt;
    rolliha(string S, int k){
        int slen = S.size();
        bt = 1;
        for(int i = 0; i < k; i++) bt *= base;
        ull sb = 0;
        for(int i = 0; i < k; i++) sb = sb * base + (ull) S[i];
        for(int i = 0; i + k <= slen; i++){
            m[sb]++;
            if(i + k < slen) sb = sb * base - bt * (ull)S[i] + (ull)S[i + k];
        }
    }

    int judge(string T){//Tの長さは必ずk
        int tlen = T.size();
        ull tb = 0;
        for(int i = 0; i < tlen; i++) tb = tb * base + (ull) T[i];
        return m.count(tb);
    }
};
*/
//2^61 - 1を除数とするローリングハッシュの実装(安全)
typedef unsigned long long ull;
struct RollingHash{
    static const ull MOD = (1UL << 61) - 1;
    static const ull MASK30 = (1UL << 30) - 1;
    static const ull MASK31 = (1UL << 31) - 1;
    const ull base;
    static const ull POSITIVIZER = MOD * 4;
    vector<ull> power_mod;
    RollingHash(ull b = rand_base()) : base(b), power_mod({1}){};
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
        if(power_mod.size() < sz + 1){
            int pre_sz = power_mod.size();
            power_mod.resize(sz + 1);
            for(int i = pre_sz - 1; i < sz; i++){
                power_mod[i + 1] = CalMod(Mul(power_mod[i], MOD));
            }
        }
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
    //文字列(または配列)のS[l,...,r]部分のハッシュ値を返す(r > l)
    ull query(vector<ull> &hash, int l, int r){
        assert(r >= l);
        expand(r - l);
        ull h = CalMod(POSITIVIZER + hash[r] - Mul(hash[l], power_mod[r - l]));
    }
    int LCP(vector<ull>&a, int l1, vector<ull>&b, int l2){
        int len = min((int)a.size() - l1, (int)b.size() - l2);
        int lb = 0, ub = len + 1;
        while(ub - lb > 1){
            int mid = (ub + lb) / 2;
            if(query(a, l1, l1 + mid) == query(b, l2, l2 + mid)) lb = mid;
            else ub = mid;
        }
        return lb;
    }
};