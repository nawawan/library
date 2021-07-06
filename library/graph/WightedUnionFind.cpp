#include <vector>
using namespace std;
template<typename T>
struct UnionFind{
    vector<int> par;
    vector<int> rank;
    vector<T> dweight;
    UnionFind(int n){
        par.resize(n);
        rank.resize(n);
        dweight.resize(n);
        for(int i = 0; i < n; i++){
            par[i] = i;
            rank[i] = 1;
        }
    }

    int root(int x){
        if(par[x] == x) return x;
        else {
            int r = root(par[x]);
            dweight[x] += dweight[par[x]];
            return par[x] = r;
        }
    }

    bool same(int x, int y){
        return root(x) == root(y);
    }

    void unite(int x, int y, T w){
        w += weight(x);
        w -= weight(y):
        x = root(x);
        y = root(y);
        if(x == y) return false;
        if(rank[x] < rank[y]) {
            swap(x, y);
            w *= -1;
        }
        par[y] = x;
        rank[x] += rank[y];
        dweight[y] = w;
        return true;
    }
    T weight(int x){
        root(x);
        return dweight[x];
    }
    T diff(int x, int y){
        return weight(y) - weight(x);
    }
    int size(int x) {
        return rank[root(x)];
    }
};
