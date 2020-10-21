#include <iostream>
using namespace std;
//ax + by = 1をとく(解はx, y)
long long extgcd(long long a, long long b, long long &x, long long &y){
    int d = a;
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



long long gcd(long long x, long long y){
    if(x < y) swap(x, y);
    if(x % y == 0) return y;
    return gcd(y, x % y);
}
long long lcm(long long x, long long y){
    long long g = gcd(x, y);
    return x / g * y;
}