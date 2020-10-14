#include <iostream>
#include <vector>
#include <string>
#include <map>
using namespace std;
typedef unsigned long long ull;
const ull base = 1e9 + 7;//除数は2^64と考える
//オーバーフロー = 「MODをとること」となっている

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