#include <iostream>
using namespace std;
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

//garnerのアルゴリズム
//O(n^2)(nはmodの数)
// x = r[i](mod m[i])を満たす最小の整数xを返す
// rのサイズ == mのサイズは暗黙の了解
// あるサイトではm[i]の累積積を持ってやっていた(これならO(m))けど、オーバーフローする可能性あるよね
long long garner(vector<long long> &r, vector<long long> &m){
    long long x = 0;
    for(int i = 0; i < (int)r.size(); i++){
        if(i == 0) x = r[i];
        else{
            long long t = r[i] - x % m[i];
            for(int j = 0; j < i; j++){
                t *= mod_inverse(m[j], m[i]);
                t %= m[i];
            }
            if(t < 0) t += m[i];
            x += t * m[i - 1];
            if(x >= m[i]) x -= m[i];
        }
    }
}
