#include <vector>
#include <cassert>
#include <cmath>
#include <algorithm>
#include <numeric>
using namespace std;
//addとeraseを適宜変更(クエリが返す答えも適宜作る)
struct Mo{
    vector<int> lef, rig, ind;//クエリのindex
    bool f = false;
    int nl, nr, width, now = 0;//現在の左端、右端、区間の幅、現在見てるクエリ(now個目)0-indexed
    Mo(int N, int Q) : ind(Q), nl(0), nr(0), width((int)sqrt(N)) {}
    Mo(int N, int Q, vector<int>&L, vector<int>&R) : ind(Q), nl(0), nr(0), width((int)sqrt(N)), lef(L), rig(R) {}
    void insert(int l, int r){
        lef.push_back(l);
        rig.push_back(r);
    }
    void insert(vector<int>&L, vector<int>&R){
        lef = L;
        rig = R;
    }
    void build(){
        f = true;
        iota(ind.begin(), ind.end(), 0);
        sort(ind.begin(), ind.end(), [&](int x, int y){
            if(lef[x] / width != lef[y] / width) return lef[x] < lef[y];
            return (lef[x] / width % 2) ? (rig[x] > rig[y]) : (rig[x] < rig[y]);
        });
    }
    //開区間[lef[id], rig[id])に注意
    //クエリのindexを返す
    int increment(){
        assert(f);
        if(now == (int)ind.size()) return -1;
        int id = ind[now];
        while(nl > lef[id]) --nl, add(nl);
        while(nr < rig[id]) add(nr), ++nr;
        while(nl < lef[id]) erase(nl), ++nl;
        while(nr > rig[id]) --nr, erase(nr);
        ++now;
        return id;
    }
    //区間に入る時
    void add(int d);
    //区間から外れる時
    void erase(int d);
    //現在見てるクエリについて答えを返す
    //voidを適宜変更
    void query(){
        //return hoge;
    }
};