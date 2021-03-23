#include <iostream>
#include <vector>
#include <complex>
#include <cmath>
using namespace std;
typedef complex<double> CP;
void FFT(int N, vector<CP> &x, bool inverse){
    const double theta = 2 * M_PI / N;
	const CP zeta = {cos(theta), sin(theta) * (inverse ? -1 : 1)};
    if(N > 1){
        vector<CP> g, k;
        for(int i = 0; i < N; i++){
            if(i % 2 == 0) g.push_back(x[i]);
            else k.push_back(x[i]);
        }
        FFT(N / 2, g, inverse);
        FFT(N / 2, k, inverse);
        CP p = {1, 0};
        for(int i = 0; i < N; i++){
            x[i] = g[i % (N / 2)] + p * k[i % (N / 2)];
            p *= zeta;
        }
    }
    return;
}

template<typename T>
vector<CP> convolution(vector<T> a, vector<T> b){
    int sz = 1;
    while(sz <= a.size() + b.size()) sz *= 2;
    vector<CP> A(sz), B(sz), C(sz);
    for(int i = 0; i < (int)a.size(); ++i){
        A[i] = {(double)a[i], 0};
    }
    for(int i = 0; i < (int)b.size(); ++i){
        B[i] = {(double)b[i], 0};
    }
    FFT(sz, A, false);
    FFT(sz, B, false);
    for(int i = 0; i < sz; ++i) C[i] = A[i] * B[i];
    iFFT(sz, C, true);
    for(int i = 0; i < sz; ++i) C[i] /= sz;
    return C;
}