//オイラー関数を作成する。
//MOD mと互いに素なxについて、オイラー関数をφとすると
//x^φ = 1 (mod m)となる。φはmから一意に定まる。O(√m)
#include <iostream>
#include <vector>
using namespace std;
long long euler_phi(long long n){
    long long res = n;
    for(long long i = 0; i * i < n; i++){
        if(n % i == 0){
            res = res / i * (i - 1);
            while(n % i == 0) n /= i;
        }
    }
    if(n != 1) res = res / n * (n - 1);
    return res;
}

vector<long long> euler_phi2(int n){//エラトステネスの篩的オイラー関数の値のテーブルの作成O(nlogn)?
    vector<long long> vec(n);
    for(int i = 0; i < n; i++) vec[i] = i;
    for(int i = 2; i < n; i++){
        if(vec[i] == i){
            for(int j = i; j < n; j+= i) vec[j] = vec[j] / i * (i - 1);
        }
    }
    return vec;
}