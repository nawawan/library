#include <iostream>
#include <complex>
#include <vector>
#include <algorithm>
using namespace std;
struct P{
    long long x;
    long long y;
    int id;
    P() : x(0), y(0), id(0) {}
    P(long long X, long long Y, int ind) : x(X), y(Y), id(ind) {}
    long long dot(P p){
        return x * p.x + y * p.y;
    }
    long long det(P p){
        return x * p.y - y * p.x;
    }
    P& operator+= (const P &p){
        x += p.x;
        y += p.y;
        return *this;
    }
    P& operator-= (const P &p){
        x -= p.x;
        y -= p.y;
        return *this;
    }
    P operator+(const P &p){
        return P(*this) += p;
    }
    P operator-(const P &p){
        return P(*this) -= p;
    }
};
struct totuhou{
    totuhou(){}
    vector<P> make(vector<P> p){
        sort(p.begin(), p.end(), [&](P a, P b){
            if(a.x != b.x) return a.x < b.x;
            return a.y < b.y;
        });
        int sz = 0;
        vector<P> qs(p.size() * 2);
        for(int i = 0; i < (int)p.size(); ++i){
            while(sz > 1 && (qs[sz - 1] - qs[sz - 2]).det(p[i] - qs[sz - 1]) < 0) --sz;
            qs[sz++] = p[i];
        }
        for(int i = (int)p.size() - 2, t = sz; i >= 0; --i){
            while(sz > t && (qs[sz - 1] - qs[sz - 2]).det(p[i] - qs[sz - 1]) < 0) --sz;
            qs[sz++] = p[i];
        }
        qs.resize(sz - 1);
        return qs;
    }
};