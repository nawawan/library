#include <vector>
#include <queue>
#include <algorithm>
#include <limits>
#include <cassert>
using namespace std;

template<typename T>
struct LiChaoTree{
private:
    struct line{
        T a, b;
    };
    vector<T> x;
    vector<line> dat;
    int sz, xsize;
    bool flag;
    T INF;
    bool comp(T X, T Y, bool f){
        if(f) return X > Y;
        return X < Y;
    };
public:
    //X : クエリで飛んでくるx座標
    //f : true -> 最大値クエリ, false -> 最小値クエリ
    LiChaoTree(vector<long long>X, bool f) : flag(f) {
        sz = 1;
        sort(X.begin(), X.end());
        X.erase(unique(X.begin(), X.end()), X.end());
        xsize = X.size();
        while(sz < xsize){
            sz <<= 1;
        }
        INF = numeric_limits<T>::max();
        if(f) INF *= -1;
        x = X;
        x.resize(sz, abs(INF) / 3000000000LL);
        dat.resize(2 * sz, {0, INF});
    }
    T get(line t, T X){
        return t.a * X + t.b;
    }
    void add(line t){
        int id = 1;
        int xl = 0, xr = sz;
        while(xr - xl > 1){
            int mid = (xl + xr) / 2;
            T lx = get(t, x[xl]), rx = get(t, x[xr - 1]), mx = get(t, x[mid]);
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
    T query(T X){
        int ind = lower_bound(x.begin(), x.end(), X) - x.begin();
        T res = INF;
        ind += sz;
        while(ind > 0){
            if(!flag) res = min(res, get(dat[ind], X));
            else res = max(res, get(dat[ind], X));
            ind >>= 1;
        }
        return res;
    }
};