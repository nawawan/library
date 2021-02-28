/*EPS = 1e(-9)とでもおいて誤差をなくす
例えばdouble aについて、a < 0　や a <= 0が正しく判定されない場合があるので
int judge(double a){
    return (a < EPS ? -1: (a > EPS ? 1: 0));
}
を定義してそれで判定するなど…

STLのcomplexをベクトルとして用いると楽
complex<double> a(1.0, 2.0), b(2.0, 3.0);//1 + 2jと2 + 3j
内積…　real(a * conj(b));
外積…  complex<double> c(b.imag(), b.real()); real(a*c);*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <complex>
using namespace std;
typedef complex<double> P;
double EPS = 1e-9;
bool same(double a, double b){
    if(abs(a - b) < EPS) return true;
    return false;
}
int main(){
    vector<P> vec(8);
    vec[0] = {2.0, 5.0};
    vec[1] = {2.0, 10.0};
    vec[2] = {2.0, 4.0};
    vec[3] = {1.0, -1.0};
    vec[4] = {10.0, 2.0};
    vec[5] = {10.0, 5.0};
    vec[6] = {10.0, 3.0};
    vec[7] = {4.0, 5.0};
    sort(vec.begin(), vec.end(), [&](P a, P b){
        if(!same(a.real(), b.real())) return a.real() < b.real();
        return a.imag() < b.imag();
    });
    for(int i = 0; i < 8; i++) cout << vec[i].real() << ' ' << vec[i].imag() << endl;
}
    bool same(double a, double b){
        if(abs(a - b) < EPS) return true;
        return false;
    }
    double juze(double a){
        if(abs(a) < EPS) return 0;
        else return a;
    }
    double dot(P a, P b){
        return juze(real(a * conj(b)));
    }
    double det(P a, P b){
        P c = P(b.imag(), b.real());
        return juze(real(a * c));
    }