//行列ライブラリの作成
#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>
using namespace std;
template<typename T> struct mat{
    vector<vector<T>> matrix;//行列
    int N, M;
    mat(){}
    mat(int n, int m): N(n), M(m){
        matrix.resize(n, vector<T>(m));
    }
    mat(vector<vector<T>> m) : N(m.size()), M(m[0].size()), matrix(m){}
    vector<T> operate(vector<T> &vec){//ベクトルにかける
        assert(vec.size() == M);
        vector<T> res(N);
        for(int i = 0; i < N; i++){
            for(int j = 0; j < M; j++) res[i] += (*this)[i][j] * vec[j];
        }
        return res;
    }
    mat I(int N){
        mat m(N, N);
        for(int i = 0; i < N; i++) m[i][i] = 1;
        return (m);
    }
    mat& pow(long long K){
        assert(N == M);//正方行列である必要あり
        mat temp(I(N));
        while(K > 0){
            if(K & 1) temp *= *this;
            *this *= *this;
            K >>= 1;
        }
        matrix.swap(temp.matrix);
        return *this;
    }
    const vector<T> &operator[](int i) const{
        return matrix.at(i);
    }
    vector<T>& operator[](int i){
        return matrix.at(i);
    }
    mat& operator*=(const mat &mat2){
        vector<vector<T>> res(N, vector<T>(M));
        for(int i = 0; i < N; i++){
            for(int j = 0; j < N; j++){
                for(int k = 0; k < M; k++){
                    res[i][j] += (*this)[i][k] * mat2[k][j];
                }
            }
        }
        matrix.swap(res);
        return *this;
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