#include <iostream>
#include <vector>
#include <algorithm>
#include <complex>
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
    bool operator!=(const modint &m){
        return modint(*this).val != m.val;
    }
    bool operator!=(const int &m){
        return modint(*this).val != m;
    }
};
template<const int mod = 998244353, const int primitive_root = 3>
struct NTT{
    const int proot = primitive_root;//998244353の原始根
    using mint = modint<mod>;
    vector<mint> root, iroot;//変換と逆変換用
    vector<int> ind;//bit反転後のindex
    NTT(){
        int temp = mod - 1;
        int cnt = 0;
        while(temp % 2 == 0){
            temp >>= 1;
            ++cnt;
        }
        int LIMIT = cnt;
        root.resize(LIMIT + 1);
        iroot.resize(LIMIT + 1);
        root[LIMIT] = repow((long long)proot, temp);
        iroot[LIMIT] = root[LIMIT].inv();
        for(int i = LIMIT - 1; i >= 0; --i){
            root[i] = root[i + 1] * root[i + 1];
            iroot[i] = iroot[i + 1] * iroot[i + 1];
        }
    }
    int get_mod(){
        return mod;
    }
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
    void ntt(int sz, vector<mint> &a, bool inverse){
        int index = 1;
        for(int end = 2; end <= sz; end *= 2){
            mint w = (inverse ? iroot[index] : root[index]);
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
            ++index;
        }
        if(inverse){
            mint t = mint(sz).inv();
            for(int i = 0; i < sz; ++i) a[i] *= t;
        }
    }
    //nは必ず2のべき乗
    void bit_inv(int n){
        if(ind.size() == n) return;
        ind.resize(n);
        int cnt = __builtin_popcount(n - 1);
        for(int i = 0; i < n; ++i){
            ind[i] = 0;
            int t = i;
            int temp = 0;
            while(t > 0){
                if(t & 1) ind[i] |= (1 << (cnt - 1 - temp));
                t >>= 1;
                ++temp;
            }
        }
    }
    template<typename T>
    vector<T> convolution(vector<T> &a, vector<T> &b){
        int sz = 1;
        int N = a.size(), M = b.size();
        while(sz < N + M - 1) sz *= 2;
        assert(sz >= N + M - 1);
        vector<mint> A(sz), B(sz);
        bit_inv(sz);
        //バタフライ演算用のbit反転
        for(int i = 0; i < N; ++i) A[ind[i]] = a[i];
        for(int i = 0; i < M; ++i) B[ind[i]] = b[i];
        ntt(sz, A, false);
        ntt(sz, B, false);
        vector<mint> C(sz);
        for(int i = 0; i < sz; ++i) C[ind[i]] = A[i] * B[i];
        ntt(sz, C, true);
        C.resize(N + M - 1);
        vector<T> res(N + M - 1);
        for(int i = 0; i < N + M - 1; ++i) res[i] = C[i].val;
        return res;
    }
};
template<typename T>
struct FormalPowerSeries : vector<T>{
    NTT<998244353, 3> ntt;
    using vector<T>::vector;
    using vector<T>::operator=;
    using FPS = FormalPowerSeries;

    FPS operator+(const FPS &r){
        return FPS(*this) += r;
    }
    FPS operator-(const FPS &r){
        return FPS(*this) -= r;
    }
    FPS operator*(const FPS &r){
        return FPS(*this) *= r;
    }
    FPS operator/(const FPS &r){
        return FPS(*this) /= r;
    }
    FPS operator*(const T &r){
        return FPS(*this) *= r;
    }
    FPS operator/(const T &r){
        return FPS(*this) /= r;
    }
    FPS operator+=(const FPS &r){
        const int n = (*this).size(), m = r.size();
        for(int i = 0; i < min(n, m); ++i) (*this)[i] += r[i];
    }
    FPS operator-=(const FPS &r){
        const int n = (*this).size(), m = r.size();
        for(int i = 0; i < min(n, m); ++i) (*this)[i] -= r[i];
    }
    FPS operator*=(const FPS &r){
        const int n = (*this).size();
        (*this) = ntt.convolution((*this), r);//998244353の場合
        (*this).resize(n);
        return *this;
    }
    FPS operator*=(const T &r){
        for(auto &e: (*this)) e *= r;
    }
    FPS operator/=(const T &r){
        T inv = T(1) / r;
        for(auto &e: (*this)) e *= r;
    }
    FPS diff(){
        const int n = (*this).size();
        FPS ret(max(0, n - 1));
        for(int i = 1; i < n; ++i) ret[i - 1] = (*this)[i] * i;
        return ret;
    }
    FPS integral(){
        const int n = (*this).size();
        FPS ret(n + 1);
        T temp = T(1);
        for(int i = 0; i < n; ++i) ret[i + 1]  = (*this)[i];
        for(int i = 1; i <= n; ++i){
            ret[i] *= temp;
            temp *= i;
        }
        temp = temp.inv();
        for(int i = n; i > 0; --i){
            ret[i] *= temp;
            temp *= i;
        }
    }
    FPS inv(){
        int n = 1;
        int pri_size = (*this).size();
        assert(n != 0 && (*this)[0] != 0);
        while(pri_size > n) n <<= 1;
        (*this).resize(n);
        FPS ret = {(*this)[0].inv()};
        ret.resize(n);
        int sz = 1;
        while(sz < n){
            sz <<= 1;
            FPS f(begin(*this), begin(*this) + sz);
            FPS r(begin(ret), begin(ret) + sz);
            f.resize(sz * 2);
            r.resize(sz * 2);
            ntt.bit_inv(sz * 2);
            for(int i = 0; i < sz * 2; ++i){
                if(ntt.ind[i] < i){
                    swap(f[i], f[ntt.ind[i]]);
                    swap(r[i], r[ntt.ind[i]]);
                }
            }
            ntt.ntt(sz * 2, f, false);
            ntt.ntt(sz * 2, r, false);
            for(int i = 0; i < sz * 2; ++i){
                f[i] = f[i] * r[i] * r[i]; 
            }
            for(int i = 0; i < sz * 2; ++i){
                if(ntt.ind[i] < i) swap(f[i], f[ntt.ind[i]]);
            }
            ntt.ntt(sz * 2, f, true);
            for(int i = 0; i < sz; ++i){
                ret[i] = ret[i] + ret[i] - f[i];
            }
        }
        (*this).resize(pri_size);
        ret.resize(pri_size);
        return ret;
    }
};