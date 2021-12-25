#include <vector>
#include <queue>
#include <algorithm>
#include <limits>
#include <cassert>
using namespace std;

struct LiChaoTree{
private:
    using line = pair<long long, long long>;
    vector<long long> x;
    vector<line> dat;
    int sz, xsize;
    bool flag;
    bool comp(long long X, long long Y, bool f){
        if(f) return X > Y;
        return X < Y;
    };
    long long get(line t, long long X){
        return t.first * X + t.second;
    }
    void add_line(line t, int id, int xl, int xr){
        while(xr - xl > 1){
            int mid = (xl + xr) / 2;
            long long lx = get(t, x[xl]), rx = get(t, x[xr - 1]), mx = get(t, x[mid]);
            bool bl = comp(lx, get(dat[id], x[xl]), flag);
            bool br = comp(rx, get(dat[id], x[xr - 1]), flag);
            bool bm = comp(mx, get(dat[id], x[mid]), flag);
            if(bl && br){
                dat[id] = t;
                return;
            }
            if(!bl && !br) return;
            if(bm) swap(dat[id], t);
            if(bl != bm){
                id = (id << 1);
                xr = mid;
            }
            else{
                id = (id << 1 | 1);
                xl = mid;
            }
        }
        if(comp(get(t, x[xl]), get(dat[id], x[xl]), flag)) dat[id] = t;
    }
public:
    long long INF;
    //X : クエリで飛んでくるx座標
    //f : true -> 最大値クエリ, false -> 最小値クエリ
    LiChaoTree(vector<long long>X, bool f = false) : flag(f) {
        sz = 1;
        sort(X.begin(), X.end());
        X.erase(unique(X.begin(), X.end()), X.end());
        xsize = X.size();
        while(sz < xsize){
            sz <<= 1;
        }
        INF = numeric_limits<long long>::max();
        if(f) INF *= -1;
        x = X;
        x.resize(sz, abs(INF) / 3000000000LL);
        dat.resize(2 * sz, {0, INF});
    }
    void add(line t){
        add_line(t, 1, 0, sz);
    }
    void add(line t, long long l, long long r){
        int idl = lower_bound(x.begin(), x.end(), l) - x.begin();
        int idr = lower_bound(x.begin(), x.end(), r) - x.begin();
        int tl = idl, tr = idr;
        idl += sz;
        idr += sz;
        int szl = 1, szr = 1;
        while(idl < idr){
            if(idl & 1){
                add_line(t, idl, tl, tl + szl);
                tl += szl;
                ++idl;
            }
            if(idr & 1){
                --idr;
                add_line(t, idr, tr - szr, tr);
                tr -= szr;
            }
            idr >>= 1;
            idl >>= 1;
            szl <<= 1;
            szr <<= 1;
        }
    }
    long long query(long long X){
        int ind = lower_bound(x.begin(), x.end(), X) - x.begin();
        long long res = INF;
        ind += sz;
        while(ind > 0){
            if(!flag) res = min(res, get(dat[ind], X));
            else res = max(res, get(dat[ind], X));
            ind >>= 1;
        }
        return res;
    }
};