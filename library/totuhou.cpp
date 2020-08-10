#include <iostream>
#include <complex>
#include <vector>
#include <algorithm>
using namespace std;
typedef complex<double> P;
struct totuho{
    double EPS;
    totuho(){
        EPS = 1e-10;
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
    vector<P> make(vector<P> p, int n){
        EPS = 1e-10;
        sort(p.begin(), p.end(), [&](P a, P b){
            if(!same(a.real(), b.real())) return a.real() < b.real();
            return a.imag() < b.imag(); 
        });
        int k = 0;
        vector<P> qs(n * 2);
        for(int i = 0; i < n; i++){//下側凸包
            while(k > 1 && det(qs[k - 1] - qs[k - 2], p[i] - qs[k - 1]) <= 0) k--;
            qs[k++] = p[i];
        }
        for(int i = n - 2, t = k; i >= 0; i--){
            while(k > t && det(qs[k - 1] - qs[k - 2], p[i] - qs[k - 1]) <= 0) k--;
            qs[k++] = p[i];
        }
        qs.resize(k - 1);
        return qs;
    }
};