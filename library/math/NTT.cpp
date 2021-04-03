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
template<const int mod = 998244353, const int primitive_root = 3>
struct NTT{
    const int proot = primitive_root;//998244353の原始根
    using mint = modint<mod>;
    vector<mint> root, iroot;//変換と逆変換用
    vector<int> ind;
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
long long extgcd(long long a, long long b, long long &x, long long &y){
    long long d = a;
    if(b != 0){
        d = extgcd(b, a % b, y, x);
        y -= (a / b) * x;
    }
    else{
        x = 1;
        y = 0;
    }
    return d;
}
long long mod_inverse(long long a, long long m){
    long long x, y;
    extgcd(a, m, x, y);
    return (m + x % m) % m;
}
template<typename T> 
vector<long long> arbitrary_convolution(vector<T> &a, vector<T> &b, const int mod){
    for(auto &x: a) x %= mod;
    for(auto &x: b) x %= mod;
    NTT<167772161, 3> ntt1;
    NTT<469762049, 3> ntt2;
    NTT<1224736769, 3> ntt3;
    vector<long long> x = ntt1.convolution(a, b);
    vector<long long> y = ntt2.convolution(a, b);
    vector<long long> z = ntt3.convolution(a, b);
    //garnerで復元
    vector<long long> res(x.size());
    vector<long long> M = {ntt1.get_mod(), ntt2.get_mod(), ntt3.get_mod()};
    const long long m12 = mod_inverse(M[0], M[1]);
    const long long m123 = mod_inverse(M[0] * M[1], M[2]);
    const long long m12_m = M[0] * M[1] % mod;
    for(int i = 0; i < (int)x.size(); ++i){
        long long temp = x[i];
        long long t = (y[i] - x[i]) * m12 % M[1];
        if(t < 0) t += M[1];
        temp = temp + M[0] * t;
        t = (z[i] - temp % M[2]) * m123 % M[2];
        if(t < 0) t += M[2];
        res[i] = (temp + m12_m * t) % mod;
    }
    return res;
}