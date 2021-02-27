#include <iostream>
#include <vector>
#include <cassert>
using namespace std;
//ax + by = gcd(x, y)をとく(解はx, y)
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
//連立線形合同式をときます(必ず最小値を返す)
//返り値は、x = a (mod z) となる{a, z}を返す
//解がない時は{0, -1}を返す
//まぁ計算量はO(Nlog(maxM))かな
pair<long long, long long> crt(vector<long long> B, vector<long long>M){
    assert(B.size() == M.size());
    assert(B.size() > 1);
    int N = B.size();
    long long x = 0, m = 1;
    for(int i = 0; i < N; i++){
        if(i == 0){
            x = B[i], m = M[i];
        }
        else{
            long long p, q;
            long long d = extgcd(m, M[i], p, q);
            if((B[i] - x) % d) return {0, -1};
            long long lcm = m / d * M[i];
            long long t = M[i] / d;
            long long temp = (B[i] - x) / d * p % t;
            if(temp < 0) temp += t;
            x = (x + m * temp) % lcm;
            m = lcm;
        }
    }
    return {x, m};
}


long long gcd(long long x, long long y){
    if(x < y) swap(x, y);
    if(x % y == 0) return y;
    return gcd(y, x % y);
}
long long lcm(long long x, long long y){
    long long g = gcd(x, y);
    return x / g * y;
}