#include <cmath>

const long double EPS = 1e-10;
long double add(long double x, long double y){
    if(abs(x + y) < EPS * (abs(x) + abs(y)) ) return 0;
    return x + y;
}
struct PL{
    long double x, y;
    PL() {}
    PL(long double x, long double y) : x(x), y(y) {
    }
    PL operator + (PL p){
        return PL(add(x, p.x), add(y, p.y));
    }
    PL operator - (PL p){
        return PL(add(x, -p.x), add(y, -p.y));
    }
    PL operator * (long double d){
        return PL(x * d, y * d);
    }
    long double dot(PL p){
        return add(x * p.x, y * p.y);
    }
    long double det(PL p){
        return add(x * p.y, -y * p.x);
    }
    long double norm(){
        return sqrt(add(x * x, y * y));
    }
};