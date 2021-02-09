//行列ライブラリの作成
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
template<typename T> struct mat{
    int N, M;//N x Mの行列(通常はN = M)
    vector<vector<T>> matrix;//行列
    mat() : N(0), M(0), matrix(0){}
    mat(int n, int m){
        N = n;
        M = m;
        matrix.resize(N, vector<T>(M));
    }
    mat(vector<vector<T>> m){
        N = m.size();
        M = m[0].size();
        matrix = m;
    }
    mat(int n, int m, vector<vector<T>> m1){
        N = n;
        M = m;
        matrix = m1;
    }
    void init(vector<vector<T>> m){
        N = m.size();
        M = m[0].size();
        matrix = m; 
    }
    mat mulmod(const mat &mat2, const T MOD){
        mat res(N, M);
        for(int i = 0; i < N; i++){
            for(int j = 0; j < N; j++){
                for(int k = 0; k < M; k++){
                    res.matrix[i][j] += (*this).matrix[i][k] * mat2.matrix[k][j] % MOD;
                    if(res.matrix[i][j] >= MOD) res -= MOD;
                }
            }
        }
        return res;
    }
    vector<T> operate(vector<T> vec){
        assert(vec.size() == M);
        vector<T> res(N);
        for(int i = 0; i < N; i++){
            for(int j = 0; j < M; j++) res[i] += matrix[i][j] * vec[j];
        }
        return res;
    }
    vector<T> operate(vector<T> vec, const T MOD){
        assert(vec.size() == M);
        vector<T> res(N);
        for(int i = 0; i < N; i++){
            for(int j = 0; j < M; j++){
                res[i] += matrix[i][j] * vec[j] % MOD;
                if(res[i] >= MOD) res[i] -= MOD;
            }
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
    vector<T> repow(T K, vector<T> vec, const T MOD){//行列累乗(MODあり)
        assert(N == M);
        while(K > 0){
            if(K & 1) vec = operate(vec, MOD);
            vector<vector<T>> temp(N, vector<T>(M));
            for(int i = 0; i < N; i++){
                for(int j = 0; j < N; j++){
                    for(int k = 0; k < N; k++){
                        temp[i][j] += matrix[i][k] * matrix[k][j] % MOD;
                        if(temp[i][j] >= MOD) temp[i][j] -= MOD;
                    }
                }
            }
            matrix.swap(temp);
            K >>= 1;
        }
        return vec;
    }
    vector<vector<T>> repow(T K, vector<vector<T>> m, const T MOD){//行列累乗(MODあり)単位行列とかとかける
        assert(N == M && m.size() == N && m[0].size() == M);
        mat m1(m);
        while(K > 0){
            if(K & 1) m1 = mulmod(m1, MOD);
            vector<vector<T>> temp(N, vector<T>(M));
            for(int i = 0; i < N; i++){
                for(int j = 0; j < N; j++){
                    for(int k = 0; k < N; k++){
                        temp[i][j] += matrix[i][k] * matrix[k][j] % MOD;
                        if(temp[i][j] >= MOD) temp[i][j] -= MOD;
                    }
                }
            }
            matrix.swap(temp);
            K >>= 1;
        }
        return m1.matrix;
    }
    mat operator+(const vector<vector<T>> &mat2){
        mat res(N, M);
        for(int i = 0; i < N; i++){
            for(int j = 0; j < M; j++) res.matrix[i][j] = (*this).matrix[i][j] + mat2[i][j]; 
        }
        return res;
    }
    mat operator+(const mat &mat1){
        mat res(N, M);
        for(int i = 0; i < N; i++){
            for(int j = 0; j < M; j++) res.matrix[i][j] = (*this).matrix[i][j] + mat1.matrix[i][j]; 
        }
        return res;
    }
    mat operator-(const mat &mat1){
        mat res(N, M);
        for(int i = 0; i < N; i++){
            for(int j = 0; j < M; j++) res.matrix[i][j] = (*this).matrix[i][j] - mat1.matrix[i][j]; 
        }
        return res;
    }
    mat operator-( const vector<vector<T>> &mat2){
        mat res(N, M);
        for(int i = 0; i < N; i++){
            for(int j = 0; j < M; j++) res.matrix[i][j] = (*this).matrix[i][j] - mat2[i][j]; 
        }
        return res;
    }
    mat operator*(const mat &mat2){
        mat res(N, M);
        for(int i = 0; i < N; i++){
            for(int j = 0; j < N; j++){
                for(int k = 0; k < M; k++){
                    res.matrix[i][j] += (*this).matrix[i][k] * mat2.matrix[k][j];
                }
            }
        }
        return res;
    }
    mat& operator+=(const mat &mat2){
        assert(N == mat2.N && M == mat2.M);
        for(int i = 0; i < N; i++){
            for(int j = 0; j < M; j++) (*this).matrix[i][j] += mat2.matrix[i][j];
        }
        return *this;
    }
    mat& operator-=(const mat &mat2){
        assert(N == mat2.N && M == mat2.M);
        for(int i = 0; i < N; i++){
            for(int j = 0; j < M; j++) (*this).matrix[i][j] -= mat2.matrix[i][j];
        }
        return *this;
    }
    mat& operator+=(const vector<vector<T>> &mat2){
        assert(N == mat2.size() && M == mat2[0].size());
        for(int i = 0; i < N; i++){
            for(int j = 0; j < M; j++) (*this).matrix[i][j] += mat2[i][j];
        }
        return *this;
    }
    mat& operator-=(const vector<vector<T>> &mat2){
        assert(N == mat2.size() && M == mat2[0].size());
        for(int i = 0; i < N; i++){
            for(int j = 0; j < M; j++) (*this).matrix[i][j] -= mat2[i][j];
        }
        return *this;
    }
};