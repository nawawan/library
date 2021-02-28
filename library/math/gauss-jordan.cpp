#include <iostream>
#include <vector>
using namespace std;
const double EPS = 1e-8;
typedef vector<double> vec;
typedef vector<vec> mat;
vec gauss_jordan(const mat & A, const vec &b){
    int n = A.size();//n個の連立方程式をとく。
    mat B(n, vec(n + 1));
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++) B[i][j] = A[i][j];
    }
    for(int i = 0; i < n; i++) B[i][n] = b[i];
    for(int i = 0; i < n; i++){//誤差を小さくするために消す変数の係数の絶対値が大きいように変更する
        int index = i;
        for(int j = i; j < n; j++){
            if(abs(B[j][i]) > abs(B[index][i])) index = j;
        }
        swap(B[i], B[index]);
        if(abs(B[i][i]) < EPS) return vec();//解が一意出ないなら長さ0の配列をかえす。
        for(int j = i + 1; j <= n; j++) B[i][j] /= B[i][i];
        for(int j = 0; j < n; j++){
            if(i != j){
                for(int k = i + 1; k <= n; k++) B[j][k] -= B[j][i] * B[i][k];
            }//厳密には単位行列 + ベクトルとはなっていないが、一応解は求められている。
        }
    }
    vec x(n);
    for(int i = 0; i < n; i++) x[i] = B[i][n];
    return x;
}