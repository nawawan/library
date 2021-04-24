//行列ライブラリの作成
#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>
using namespace std;
//少なくとも行列累乗はクソ遅いので、使わないほうがいいよ
template<typename T> struct mat{
    vector<vector<T>> matrix;//行列
    int N, M;
    //const int MOD//必要なら
    mat() : N(0), M(0), matrix(0){}
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
    vector<T> repow(long long K, vector<T> &vec){//行列累乗(MODなし)
        assert(N == M);//正方行列である必要あり
        while(K > 0){
            if(K & 1) vec = operate(vec);
            mat temp(*this);
            temp = (*this) * (*this);
            matrix.swap(temp.matrix);
            K >>= 1;
        }
        return vec;
    }
    vector<T> operator[](const int i) const{
        return matrix.at(i);
    }
    vector<T>& operator[](const int i){
        return matrix.at(i);
    }
    mat& operator=(mat m){
        matrix.swap(m.matrix);
        return *this;
    }
    mat& operator*=(const mat &mat2){
        vector<vector<T>> res(N, vector<T>(M));
        for(int i = 0; i < N; i++){
            for(int j = 0; j < N; j++){
                for(int k = 0; k < N; k++){
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