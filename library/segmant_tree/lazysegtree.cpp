#include <iostream>
#include <vector>
#include <cassert>
#include <cmath>
#include <queue>
#include <stack>
using namespace std;
//抽象化セグメントツリー
/*
https://algo-logic.info/segment-tree/#toc_id_6_4
↑参考になりすぎ！
モノイドXとYを定義//
mergeは二つのXを指定した演算で結合(基本ボトムアップ)
idはidentity、Xの単位元のこと
propはpropagateのことで、二つのYを伝搬する形で結合(基本トップダウン)
affectはモノイドXに、モノイドYを用いた作用素を作用させる(この辺数学力なさすぎて説明ガバそう)
eはYの単位元
*/
/*
実装は難しいが、やってることは
値を取得 or 更新する前にlazyをトップダウンに伝搬
更新、取得する部分の部分木の根を全部探索
更新の場合は更新後ボトムアップに親を更新
*/
template<typename S, S (*merge)(S, S), S (*id)(), typename F, F (*prop)(F, F), S (*affect)(F, S), F (*e)()> struct lazy_segment_tree{
private:
    int n;
    int size;//元の配列の大きさ
    int height; //セグ木の高さの最大値 - 1
    vector<S> dat;
    vector<F> lazy;
    void update_sub(int k){
        dat[k] = merge(dat[k << 1 | 0], dat[k << 1 | 1]);
    }
    //伝搬用の関数
    void push(int k){
        operate(2 * k, lazy[k]);
        operate(2 * k + 1, lazy[k]);
        lazy[k] = e();
    }
    //伝搬してきた遅延を作用させ、遅延部分を増幅(というより結合)させる
    void operate(int k, F x){
        dat[k] = affect(x, dat[k]);
        if(k < size) lazy[k] = prop(x, lazy[k]);
    }
public:
    lazy_segment_tree(int n_) : n(n_ * 2), size(n_){
        dat.resize(n, id());
        lazy.resize(n, e())
        height = 0;
        int t = 1;
        while(t < n_){
            height++;
            t *= 2;
        }
    }
    lazy_segment_tree(vector<S> &v){
        size = (int)v.size();
        n = size * 2;
        dat.resize(n, id());
        height = 0;
        int t = 1;
        while(t < size){
            t *= 2;
            height++;
        }
        lazy.resize(n, e());
        for(int i = 0; i < size; i++) dat[i + size] = v[i];
        for(int i = size - 1; i >= 1; i--){
            update_sub(i);
        }
    }
    //区間更新
    void update(int l, int r, F a){
        int l1 = l + size;
        int r1 = r + size;
        for(int i = height; i >= 1; i--){
            if(((l1 >> i) << i) != l1 && (l1 >> i) >= 1) push(l1 >> i);
            if(((r1 >> i) << i) != r1 && (r1 >> i) >= 1) push(r1 >> i);
        }
        while(r1 > l1){
            if(l1 & 1) operate(l1++, a);
            if(r1 & 1) operate(--r1, a);
            r1 >>= 1;
            l1 >>= 1;
        }
        l1 = l + size;
        r1 = r + size;
        for(int i = 1; i <= height; i++){
            if(((l1 >> i) << i) != l1 && (l1 >> i) >= 1) update_sub(l1 >> i);
            if(((r1 >> i) << i) != r1 && (r1 >> i) >= 1) update_sub(r1 >> i);
        }
    }
    //一点更新
    void update(int ind, F a){
        ind += size;
        for(int i = height; i >= 1; i--){
            if((ind >> i) >= 1) push(ind >> i);
        }
        dat[ind] = affect(a, dat[ind]);
        for(int i = 1; i <= height; i++){
            if((ind >> i) >= 1) update_sub(ind >> i);
        }
    }
    //区間mergeを取得
    S query(int l, int r){
        if(l >= r) return id();
        S resr = id(), resl = id();
        l += size;
        r += size;
        for(int i = height; i >= 1; i--){
            if(((l >> i) << i) != l && (l >> i) >= 1) push(l >> i);
            if(((r >> i) << i) != r && (r >> i) >= 1) push(r >> i);
        }
        while(r > l){
            if(l & 1) resl = merge(resl, dat[l++]);
            if(r & 1) resr = merge(dat[--r], resr);
            l >>= 1;
            r >>= 1;
        }
        return merge(resl, resr);
    }
    S all_query(){
        return dat[1];
    }
    //[l, r)でf(merge(a[l],..., a[r - 1]))がtrueとなる最大のrを返す
    template<typename op>
    int max_right(int l, op f){
        if(l == size) return size;
        stack<int> s;
        queue<int> q;
        l += size;
        int r = n;
        for(int i = height; i >= 1; i--){
            if(((l >> i) << i) != l && (l >> i) >= 1) push(l >> i);
        }
        while(r > l){
            if(l & 1){
                q.push(l++);
            }
            if(r & 1){
                s.push(--r);
            }
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
            S temp = merge(res, dat[v]);
            if(!f(temp)){
                now = v;
                break;
            }
            res = temp;
        }
        if(now == -1) return size;
        while(now < size){
            push(now);
            now <<= 1;
            S temp = merge(res, dat[now]);
            if(f(temp)){
                res = temp;
                now++;
            }
        }
        return now - size;
    }
    //[l, r)でf(merge(a[l],..., a[r - 1]))がtrueとなる最小のlを返す
    template<typename op>
    int min_left(int r, op f){
        if(r == 0) return 0;
        stack<int> s;
        queue<int> q;
        int l = size;
        r += size;
        for(int i = height; i >= 1; i--){
            if(((r >> i) << i) != r && (r >> i) >= 1) push(r >> i);
        }
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
            S temp = merge(res, dat[v]);
            if(!f(temp)){
                now = v;
                break;
            }
            res = temp;
        }
        if(now == -1) return 0;
        while(now < size){
            push(now);
            now <<= 1;
            now++;
            S temp = merge(res, dat[now]);
            if(f(temp)){
                res = temp;
                now--;
            }
        }
        return now + 1 - size;
    }
};