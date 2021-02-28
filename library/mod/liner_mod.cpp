#include <iostream>
#include <vector>
#include <utility>
using namespace std;
//連立線形合同式をとく
typedef pair<long long, long long> P;
long long gcd(long long a, long long b){
    if(b == 0) return a;
    return gcd(b, a % b);
}
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
P liner_mod(const vector<long long> &A, const vector<long long> &B, const vector<long long> &M){
    long long x = 0, m = 1;
    for(int i = 0; i < A.size(); i++){
        long long a = A[i] * m, b = B[i] - A[i] * x, d = gcd(M[i], a);
        if(b % d != 0) return P(0, -1);//解なし
        long long t = b / d * mod_inverse(a/ d, M[i] / d) % (M[i] / d);
        x = x + m * t;
        m *= M[i] / d;
    }
    return P((x + m) % m, m);
}