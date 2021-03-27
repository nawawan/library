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