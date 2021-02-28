#include <iostream>
#include <complex>
#include <vector>
#include <algorithm>
using namespace std;
typedef complex<double> P;
double EPS = 1e-10;
bool same(double a, double b){
    if(abs(a - b) < EPS) return true;
    return false;
}
bool comp(P &a, P &b){
    if(!same(a.real(), b.real())) return a.real() < b.real();
    return a.imag() < b.imag(); 
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
vector<P> p;
vector<P> totuho(int n){
    sort(p.begin(), p.end(), comp);
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
int N;
double dis(P x, P y){
    return det(x - y, x - y);
}
void solve(){
    vector<P> qs = totuho(N);
    int n = qs.size();
    if(n == 2){//凸包が直線の時
        printf("%.0f\n", dis(qs[0], qs[1]));
        return;
    }
    int s = 0, t = 0;
    for(int k = 0; k < n; k++){
        if(!comp(qs[s], qs[k])) s = k;
        if(comp(qs[t], qs[k])) t = k; 
    }
    double res = 0;
    int sts = s, stt = t;
    while(s != stt || t != sts){
        res = max(res, dis(qs[s], qs[t]));
        if(det(qs[(s + 1) % n] - qs[s], qs[(t + 1) % n] - qs[t]) < 0) s = (s + 1) % n;
        else t = (t + 1) % n;
    }
    printf("%.0f\n", res);
}