#include <vector>
#include <stack>
#include <cassert>
#include <queue>
#include <numeric>
#include <algorithm>
using namespace std;
template<typename S, S (*XX)(S, S), S (*id)()> struct two_dimension_segment_tree{
private:
    int n, m;
    int sizen, sizem;//元の配列の大きさ
    vector<vector<S>> dat;
    vector<int> X;
    void update_sub(int k, int k2){
        int idl = lower_bound(ind[k << 1 | 0].begin(), ind[k << 1 | 0].end(), ind[k][k2]) - ind[k << 1 | 0].begin();
        int idr = lower_bound(ind[k << 1 | 1].begin(), ind[k << 1 | 1].end(), ind[k][k2]) - ind[k << 1 | 1].begin();
        if(idl == ind[k << 1].size() || ind[k << 1][idl] != ind[k][k2]) dat[k][k2 + ind[k].size()] = dat[k << 1 | 1][idr + ind[k << 1 | 1].size()];
        else if(idr == ind[k << 1 | 1].size() || ind[k << 1 | 1][idr] != ind[k][k2]) dat[k][k2 + ind[k].size()]  = dat[k << 1][idl + ind[k << 1].size()];
        else dat[k][k2 + ind[k].size()] = XX(dat[k << 1 | 0][idl + ind[k << 1].size()], dat[k << 1 | 1][idr + ind[k << 1 | 1].size()]);
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
        l = lower_bound(ind[row].begin(), ind[row].end(), l) - ind[row].begin();
        r = lower_bound(ind[row].begin(), ind[row].end(), r) - ind[row].begin();
        l += dat[row].size() / 2;
        r += dat[row].size() / 2;
        while(r > l){
            if(l & 1) vl = XX(vl, dat[row][l++]);
            if(r & 1) vr = XX(dat[row][--r], vr);
            l >>= 1;
            r >>= 1;
        }
        return XX(vl, vr);
    }
public:
    vector<vector<int>> ind;
    two_dimension_segment_tree(vector<int> &wx, vector<int> &wy, vector<S> w){
        X = wx;
        sort(X.begin(), X.end());
        X.erase(unique(X.begin(), X.end()), X.end());
        sizen = (int)X.size();
        n = sizen * 2;
        ind.resize(n);
        for(int i = 0; i < (int)wx.size(); ++i){
            int id2 = lower_bound(X.begin(), X.end(), wx[i]) - X.begin();
            ind[id2 + sizen].push_back(wy[i]);
        }
        for(int i = sizen; i < n; ++i){
            sort(ind[i].begin(), ind[i].end());
            ind[i].erase(unique(ind[i].begin(), ind[i].end()), ind[i].end());
        }
        for(int i = sizen - 1; i >= 1; --i){
            for(int j = 0; j < (int)ind[i * 2].size(); ++j) ind[i].push_back(ind[i * 2][j]);
            for(int j = 0; j < (int)ind[i * 2 + 1].size(); ++j) ind[i].push_back(ind[i * 2 + 1][j]);
            sort(ind[i].begin(), ind[i].end());
            ind[i].erase(unique(ind[i].begin(), ind[i].end()), ind[i].end());
        }
        dat.resize(n);
        for(int i = 1; i < n; ++i){
            dat[i].resize(2 * ind[i].size(), id());
        }
        for(int i = 0; i < (int)w.size(); ++i){
            int hid = lower_bound(X.begin(), X.end(), wx[i]) - X.begin();
            int wid = lower_bound(ind[hid + sizen].begin(), ind[hid + sizen].end(), wy[i]) - ind[hid + sizen].begin();
            dat[hid + sizen][wid + ind[hid + sizen].size()] = XX(dat[hid + sizen][wid + ind[hid + sizen].size()], w[i]);
        }
        for(int i = sizen - 1; i >= 1; --i){
            for(int j = 0; j < dat[i].size() / 2; ++j){
                update_sub(i, j);
            }
        }
        for(int i = 1; i < n; i++){
            for(int j = (int)dat[i].size() / 2 - 1; j >= 1; --j){
                update_column_sub(i, j);
            }
        }
    }
    S& operator[](const int i){
        return dat[i + sizen];
    }
    S get(int i, int j){
        return dat[i][j + dat[i].size() / 2];
    }
    //O(log(n)log(m))
    void update(int i, int j, S a){
        i += sizen;
        int id2 = lower_bound(ind[i].begin(), ind[i].end(), j) - ind[i].begin();
        update_column(i, id2 + dat[i].size() / 2, a);
        while(i > 1){
            i >>= 1;
            int l = lower_bound(ind[i << 1].begin(), ind[i << 1].end(), j) - ind[i << 1].begin();
            int r = lower_bound(ind[i << 1 | 1].begin(), ind[i << 1 | 1].end(), j) - ind[i << 1 | 1].begin();
            S temp = id();
            if(l != ind[i << 1].size() && ind[i << 1][l] == ind[i][id]) temp = XX(temp, dat[i << 1 | 0][l]);
            if(r != ind[i << 1 | 1].size() && ind[i << 1 | 1][r] == ind[i][id]) temp = XX(temp, dat[i << 1 | 1][r]);
            id2 = lower_bound(ind[i].begin(), ind[i].end(), j) - ind[i].begin();
            update_column(i, id2 + dat[i].size() / 2, temp);
        }
    }
    //O(log(|rr - lr|)log(|cr - cl|))？
    S query(int lr, int rr, int cl, int cr){
        lr = lower_bound(X.begin(), X.end(), lr) - X.begin();
        rr = lower_bound(X.begin(), X.end(), rr) - X.begin();
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