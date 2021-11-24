#include <vector>
#include <stack>
#include <cassert>
#include <queue>
using namespace std;
template<typename S, S (*XX)(S, S), S (*id)()> struct two_dimension_segment_tree{
private:
    int n, m;
    int sizen, sizem;//元の配列の大きさ
    vector<vector<S>> dat;
    void update_sub(int k, int k2){
        dat[k][k2] = XX(dat[k << 1 | 0][k2], dat[k << 1 | 1][k2]);
    }
    void update_column_sub(int k, int k2){
        dat[k][k2] = XX(dat[k][k2 << 1 | 0], dat[k][k2 << 1 | 1]);
    }
    void update_column(int i, int j, S a){
        dat[i][j] = a;
        while(j > 1){
            j >>= 1;
            dat[i][j] = XX(dat[i][j << 1 | 0], dat[i][j << 1 | 1]);
        }
    }
    S query_column(int row, int l, int r){
        if(l >= r) return id();
        S vl = id(), vr = id();
        l += sizem;
        r += sizem;
        while(r > l){
            if(l & 1) vl = XX(vl, dat[row][l++]);
            if(r & 1) vr = XX(dat[row][--r], vr);
            l >>= 1;
            r >>= 1;
        }
        return XX(vl, vr);
    }
public:
    two_dimension_segment_tree(int n_, int m_) : n(n_ * 2), sizen(n_), m(m_ * 2), sizem(m_){
        dat.resize(n, vector<S>(m, id()));
    }
    //構築O(nm)
    two_dimension_segment_tree(vector<vector<S>> &v){
        sizen = (int)v.size();
        sizem = (int)v[0].size();
        n = sizen * 2;
        m = sizem * 2;
        dat.resize(n, vector<S>(m, id()));
        for(int i = 0; i < sizen; ++i){
            for(int j = 0; j < sizem; j++) dat[i + sizen][j + sizem] = v[i][j];
        }
        for(int i = sizen - 1; i >= 1; --i){
            for(int j = sizem; j < sizem * 2; ++j){
                dat[i][j] = XX(v[i * 2][j], v[i << 1 | 1][j]);
            }
        }
        for(int i = 1; i < sizen * 2; ++i){
            for(int j = sizem - 1; j >= 1; --j){
                update_column_sub(i, j);
            }
        }
    }
    S& operator[](const int i){
        return dat[i + sizen];
    }
    S get(int i, int j){
        return dat[i + sizen][j + sizem];
    }
    //O(log(n)log(m))
    void update(int i, int j, S a){
        i += sizen;
        j += sizem;
        update_column(i, j, a);
        while(i > 1){
            i >>= 1;
            S temp = XX(dat[i << 1 | 0][j], dat[i << 1 | 1][j]);
            update_column(i, j, temp);
        }
    }
    //O(log(|rr - lr|)log(|cr - cl|))？
    S query(int lr, int rr, int cl, int cr){
        if(lr >= rr || cl >= cr) return id();
        S vl = id(), vr = id();
        lr += sizen;
        rr += sizen;
        while(rr > lr){
            if(lr & 1) {
                vl = XX(vl, query_column(lr++, cl, cr));
            }
            if(rr & 1) {
                vr = XX(query_column(--rr, cl, cr), vr);
            }
            lr >>= 1;
            rr >>= 1;
        }
        return XX(vl, vr);
    }
};