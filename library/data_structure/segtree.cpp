#include <iostream>
#include <vector>
#include <cassert>
using namespace std;
//抽象化セグメントツリー
/*
https://hcpc-hokudai.github.io/archive/structure_segtree_001.pdf
↑参考になりすぎ！
mergeは二つの値を指定した演算で結合(ボトムアップに更新)
idはidentity、単位元のこと
*/
template<typename S, S (*XX)(S, S), S (*id)()> struct segment_tree{
private:
    int n;
    int size;//元の配列の大きさ
    vector<S> dat;
    void update_sub(int k){
        dat[k] = XX(dat[k << 1 | 0], dat[k << 1 | 1]);
    }
public:
    segment_tree(int n_) : n(n_ * 2), size(n_){
        dat.resize(n, id());
    }
    segment_tree(vector<S> &v){
        size = (int)v.size();
        n = size * 2;
        dat.resize(n, id());
        for(int i = 0; i < size; ++i) dat[i + size] = v[i];
        for(int i = size - 1; i >= 1; --i){
            update_sub(i);
        }
    }
    S& operator[](const int i){
        return dat[i + size];
    }
    void update(int ind, S a){
        ind += size;
        dat[ind] = a;
        while(ind > 1){
            ind >>= 1;
            dat[ind] = XX(dat[ind << 1 | 0], dat[ind << 1 | 1]);
        }
    }
    S query(int l, int r){
        if(l >= r) return id();
        S vl = id(), vr = id();
        l += size;
        r += size;
        while(r > l){
            if(l & 1) vl = XX(vl, dat[l++]);
            if(r & 1) vr = XX(dat[--r], vr);
            l >>= 1;
            r >>= 1;
        }
        return XX(vl, vr);
    }
    //[l, r)でf(merge(a[l],..., a[r - 1]))がtrueとなる最大のrを返す
    template<typename F>
    int max_right(int l, F f){
        if(l == size) return size;
        stack<int> s;
        queue<int> q;
        l += size;
        int r = n;
        while(r > l){
            if(l & 1) q.push(l++);
            if(r & 1) s.push(--r);
            r >>= 1;
            l >>= 1;
        }
        while(!s.empty()){
            q.push(s.top());
            s.pop();
        }
        S res = id();
        int now = -1;
        while(!q.empty()){
            int v = q.front();
            q.pop();
            S temp = XX(res, dat[v]);
            if(!f(temp)){
                now = v;
                break;
            }
            res = temp;
        }
        if(now == -1) return size;
        while(now < size){
            now <<= 1;
            S temp = XX(res, dat[now]);
            if(f(temp)){
                res = temp;
                ++now;
            }
        }
        return now - size;
    }
    //[l, r)でf(merge(a[l],..., a[r - 1]))がtrueとなる最小のlを返す
    template<typename F>
    int min_left(int r, F f){
        if(r == 0) return 0;
        stack<int> s;
        queue<int> q;
        int l = size;
        r += size;
        while(r > l){
            if(r & 1) q.push(--r);
            if(l & 1) s.push(l++);
            r >>= 1;
            l >>= 1;
        }
        while(!s.empty()){
            q.push(s.top());
            s.pop();
        }
        S res = id();
        int now = -1;
        while(!q.empty()){
            int v = q.front();
            q.pop();
            S temp = XX(res, dat[v]);
            if(!f(temp)){
                now = v;
                break;
            }
            res = temp;
        }
        if(now == -1) return 0;
        while(now < size){
            now <<= 1;
            ++now;
            S temp = XX(res, dat[now]);
            if(f(temp)){
                res = temp;
                --now;
            }
        }
        return now + 1 - size;
    }
    //上から二分探索する用(現コードはMexを求めるようのやつ)
    int lower_bound(int f){
        int now = 0;
        while(now < size){
            if(now == 0) now += size;
            while((now & 1) == 0) now >>= 1;
            if(dat[now] < f){
                while(now < size){
                    int l = now << 1;
                    int r = (now << 1) | 1;
                    if(dat[l] < f) now = l;
                    else now = r;
                }
            }
            else ++now;
        }
        return now - size;
    }
};