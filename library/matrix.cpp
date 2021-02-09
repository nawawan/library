//行列ライブラリの作成
#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>
using namespace std;
template<typename T> struct mat{
    vector<vector<T>> matrix;//行列
    int N, M;
    //const int MOD//必要なら
    mat() : N(0), M(0), matrix(0){}
    mat(int n, int m){
        matrix.resize(n, vector<T>(m));
        N = n;
        M = m;
    }
    mat(vector<vector<T>> m){
        matrix = m;
        N = m.size();
        M = m[0].size();
    }
    vector<T> operate(vector<T> vec){//ベクトルにかける
        assert(vec.size() == M);
        vector<T> res(N);
        for(int i = 0; i < N; i++){
            for(int j = 0; j < M; j++) res[i] += matrix[i][j] * vec[j];
        }
        return res;
    }
    vector<T> repow(T K, vector<T> vec){//行列累乗(MODなし)
        assert(N == M);//正方行列である必要あり
        while(K > 0){
            if(K & 1) vec = operate(vec);
            vector<vector<T>> temp(N, vector<T>(M));
            for(int i = 0; i < N; i++){
                for(int j = 0; j < N; j++){
                    for(int k = 0; k < N; k++){
                        temp[i][j] += matrix[i][k] * matrix[k][j];
                    }
                }
            }
            matrix.swap(temp);
            K >>= 1;
        }
        return vec;
    }
    vector<T> operator[](const int i) const{
        return matrix[i];
    }
    vector<T>& operator[](const int i){
        return matrix[i];
    }
    mat& operator=(const mat& m){
        return *m;
    }
    mat& operator*=(const mat &mat2){
        mat res(N, M);
        for(int i = 0; i < N; i++){
            for(int j = 0; j < N; j++){
                for(int k = 0; k < M; k++){
                    res[i][j] += (*this)[i][k] * mat2[k][j];
                }
            }
        }
        return *this = res;
    }
    mat& operator^=(const mat &mat2){
        assert(N == mat2.N && M == mat2.M);
        for(int i = 0; i < N; i++){
            for(int j = 0; j < M; j++) (*this)[i][j] ^= mat2[i][j];
        }
        return *this;
    }
    mat& operator|=(const mat &mat2){
        assert(N == mat2.N && M == mat2.M);
        for(int i = 0; i < N; i++){
            for(int j = 0; j < M; j++) (*this)[i][j] |= mat2[i][j];
        }
        return *this;
    }
    mat& operator&=(const mat &mat2){
        assert(N == mat2.N && M == mat2.M);
        for(int i = 0; i < N; i++){
            for(int j = 0; j < M; j++) (*this)[i][j] &= mat2[i][j];
        }
        return *this;
    }
    mat& operator+=(const mat &mat2){
        assert(N == mat2.N && M == mat2.M);
        for(int i = 0; i < N; i++){
            for(int j = 0; j < M; j++) (*this)[i][j] += mat2[i][j];
        }
        return *this;
    }
    mat& operator-=(const mat &mat2){
        assert(N == mat2.N && M == mat2.M);
        for(int i = 0; i < N; i++){
            for(int j = 0; j < M; j++) (*this)[i][j] -= mat2[i][j];
        }
        return *this;
    }
    mat operator+(const mat &mat1){
        return mat(*this) += mat1;
    }
    mat operator-(const mat &mat1){
        return mat(*this) -= mat1;
    }
    mat operator*(const mat &mat2){
        return mat(*this) *= mat2;
    }
    mat operator&(const mat &mat1){
        return mat(*this) &= mat1;
    }
    mat operator|(const mat &mat1){
        return mat(*this) |= mat1;
    }
    mat operator^(const mat &mat1){
        return mat(*this) ^= mat1;
    }
};