#include <iostream>
#include <vector>
#include <cmath>
#include <complex>
using namespace std;
typedef complex<double> CP;
void fft(int sz, vector<CP> &a, bool inverse){
    int end = 2;
    while(end <= sz){
    double theta = 2 * M_PI / end;
    CP w = {cos(theta), sin(theta) * (inverse ? -1 : 1)};
    for(int i = 0; i < sz / end; i++){
        CP temp = {1, 0};
        for(int j = 0; j < end / 2; j++){
            CP s = a[i * end + j], t = a[i * end + j + end / 2] * temp;
            a[i * end + j] = s + t;
            a[i * end + j + end / 2] = s - t;
            temp *= w;
            }
        }   
    	end *= 2;
    }
}
template<typename T>
vector<long long> convolution(vector<T> &a, vector<T> &b){
    int sz = 1;
    while(sz < (int)a.size() + (int)b.size() - 1) sz *= 2;
    int cnt = __builtin_popcount(sz - 1);
    vector<int> ind(sz);
    for(int i = 0; i < sz; ++i){
        int t = i;
        int temp = 0;
        while(t > 0){
            if(t & 1) ind[i] |= (1 << (cnt - 1 - temp));
            t >>= 1;
            ++temp;
        }
    }
    vector<CP> A(sz), B(sz);
    for(int i = 0; i < (int)a.size(); ++i) A[ind[i]] = {(double)a[i], 0};
    for(int i = 0; i < (int)b.size(); ++i) B[ind[i]] = {(double)b[i], 0};
    fft(sz, A, false);
    fft(sz, B, false);
    vector<CP> C(sz);
    for(int i = 0; i < sz; ++i) C[ind[i]] = A[i] * B[i];
    fft(sz, C, true);
    vector<long long> res(sz);
    for(int i = 0; i < sz; ++i){
        res[i] = (long long)(C[i].real() / sz + 0.01);
    }
    return res;
}