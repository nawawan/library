#include <iostream>
#include <vector>
#include <cassert>
using namespace std;
template<const int MOD> struct modint{
    long long val;
    modint(): val(0) {}
    modint(long long x){
        if(x < 0) val = x % MOD + MOD;
        else val = x % MOD;
    }
    modint(const modint &t){
        val = t.val;
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
        if(val < 0) val += MOD;
        return *this;
    }
    modint& operator+=(const modint &m){
        val += m.val;
        if(val >= MOD) val -= MOD;
        return *this;
    }
    modint& operator*=(const modint &m){
        val *= m.val;
        val %= MOD;
        return *this;
    }
    modint& operator/=(modint m){
        *this *= m.inv();
        return *this;
    }
    modint inv(){
        long long x = 1, y = 0;
        long long a = val, b = MOD;
        while(b != 0){
            long long t = a / b;
            a -= t * b;
            x -= t * y;
            swap(a, b);
            swap(x, y);
        }
        x %= MOD;
        if(x < 0) x += MOD;
        return modint(x);
    }
    modint pow(long long k){
        long long res = 1;
        long long v = val;
        while(k > 0){
            if(k & 1) res = res * v % MOD;
            v = v * v % MOD;
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
};
const int MOD = 998244353;
using mint = modint<MOD>;
mint repow(long long x, long long y){
    if(y == 0) return 1;
    mint res = 1;
    mint x2 = x;
    while(y > 0){
        if(y & 1) res = res * x2;
        x2 = x2 * x2;
        y >>= 1;
    }
    return res;
}
struct NTT{
    const int proot = 3;//998244353の原始根
    const int LIMIT = 23;
    vector<mint> root, iroot;//変換と逆変換用
    NTT(){
        root.resize(LIMIT + 1);
        iroot.resize(LIMIT + 1);
        root[LIMIT] = repow((long long)proot, (MOD - 1) / (repow(2, 23).val));
        iroot[LIMIT] = root[LIMIT].inv();
        for(int i = LIMIT - 1; i >= 0; --i){
            root[i] = root[i + 1] * root[i + 1];
            iroot[i] = iroot[i + 1] * iroot[i + 1];
        }
    }
    void ntt(int sz, vector<mint> &a, bool inverse){
        int ind = 1;
        for(int end = 2; end <= sz; end *= 2){
            mint w = (inverse ? iroot[ind] : root[ind]);
            int ofs = end / 2;
            for(int i = 0; i < sz / end; ++i){
                mint zeta = 1;
                for(int j = 0; j < ofs; ++j){
                    mint s = a[i * end + j], t = a[i * end + j + ofs] * zeta;
                    a[i * end + j] = s + t;
                    a[i * end + j + ofs] = s - t;
                    zeta *= w;
                }
            }   
            ++ind;
        }
        if(inverse){
            mint t = repow(sz, MOD - 2);
            for(int i = 0; i < sz; ++i) a[i] *= t;
        }
    }
    template<typename T>
    vector<mint> convolution(vector<T> &a, vector<T> &b){
        int sz = 1;
        int N = a.size(), M = b.size();
        while(sz < N + M - 1) sz *= 2;
        vector<mint> A(sz), B(sz);
        int cnt = __builtin_popcount(sz - 1);
        //バタフライ演算用のbit反転
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
        for(int i = 0; i < N; ++i) A[ind[i]] = a[i];
        for(int i = 0; i < M; ++i) B[ind[i]] = b[i];
        ntt(sz, A, false);
        ntt(sz, B, false);
        vector<mint> res(sz);
        for(int i = 0; i < sz; ++i) res[ind[i]] = A[i] * B[i];
        ntt(sz, res, true);
        res.resize(N + M - 1);
        return res;
    }
};