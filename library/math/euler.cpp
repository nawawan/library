//オイラー関数を作成する。
//MOD mと互いに素なxについて、オイラー関数をφとすると
//x^φ = 1 (mod m)となる。φはmから一意に定まる。O(√m)
//オイラー関数 : φ(n) -> n以下の数でnと互いに素な自然数の数
#include <iostream>
#include <vector>
#include <numeric>
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
//エラトステネスの篩的オイラー関数の値のテーブルの作成O(nloglogn)?
vector<long long> euler_phi2(int n){
    vector<long long> vec(n);
    iota(vec.begin(), vec.end(), 0);
    for(int i = 2; i < n; i++){
        if(vec[i] == i){
            for(int j = i; j < n; j += i) vec[j] = vec[j] / i * (i - 1);
        }
    }
    return vec;
}