#include <iostream>
#include <vector>
using namespace std;
struct modint{
    long long val;
    modint(): val(0) {}
    modint(long long x){
        if(x < 0) val = x % mod() + mod();
        else val = x % mod();
    }
    modint(const modint &t){
        val = t.val;
    }
    static int &mod(){
        static int m = 0;
        return m;
    }
    static void set_mod(int md){
        mod() = md;
    }
    modint& operator =(const modint m){
        val = m.val;
        return *this;
    }
    modint operator -(){
        return modint(-val);
    }
    modint& operator-=(const modint &m){
        val -= m.val;
        if(val < 0) val += mod();
        return *this;
    }
    modint& operator+=(const modint &m){
        val += m.val;
        if(val >= mod()) val -= mod();
        return *this;
    }
    modint& operator*=(const modint &m){
        val *= m.val;
        val %= mod();
        return *this;
    }
    modint& operator/=(modint m){
        *this *= m.inv();
        return *this;
    }
    modint inv(){
        long long x = 1, y = 0;
        long long a = val, b = mod();
        while(b != 0){
            long long t = a / b;
            a -= t * b;
            x -= t * y;
            swap(a, b);
            swap(x, y);
        }
        x %= mod();
        if(x < 0) x += mod();
        return modint(x);
    }
    modint pow(long long k){
        long long res = 1;
        long long v = val;
        while(k > 0){
            if(k & 1) res = res * v % mod();
            v = v * v % mod();
            k >>= 1;
        }
        return modint(res);
    }
    modint operator==(const modint &m){
        return val == m.val;
    }
    modint operator+(const modint &m){
        return modint(*this) += m;
    }
    modint operator-(const modint &m){
        return modint(*this) -= m;
    }
    modint operator*(const modint &m){
        return modint(*this) *= m;
    }
    modint operator/(const modint &m){
        return modint(*this) /= m;
    }
    bool operator!=(const modint &m){
        return modint(*this).val != m.val;
    }
    bool operator!=(const int &m){
        return modint(*this).val != m;
    }
};