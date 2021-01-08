#include <iostream>
#include <vector>
using namespace std;
struct BIT{
    vector<long long> num;
    int N;
    int beki;
    BIT(int n){
        N = n;
        beki = 1;
        while(beki <= N) beki *= 2;
        beki /= 2;
        num.resize(N + 1, 0);
    }
    long long sum(long long t){
        long long res = 0;
        while(t > 0){
            res += num[t];
            t -= t & -t;
        }
        return res;
    }
    void add(int ind, long long t){
        ind++;
        while(ind <= N){
            num[ind] += t;
            ind += ind & -ind;
        }
    }
    long long get(long long k){//累積和がk以下のとなる最大のindexを返す
        int ind = 0;
        for(int i = beki; i > 0; i /= 2){
            if(ind + i <= N && num[ind + i] <= k){
                k -= num[ind + i];
                ind += i;
            }
        }
        return ind;
    }
};

/*
転倒数を求めるには
座圧して順にadd(index, 1);
sum(N) - sum(index + 1)を足す。
*/

//区間maxのBIT
struct BIT{
    vector<long long> num;
    int N;
    BIT(int n){
        N = n;
        num.resize(N + 1, 0);
    }
    long long bit_max(long long t){
        long long res = 0;
        while(t > 0){
            res = max(res, num[t]);
            t -= t & -t;
        }
        return res;
    }
    void add(int ind, long long t){
        ind++;
        int temp = ind;
        while(ind <= N){
            num[ind] = max(num[ind], t);
            ind += ind & -ind;
        }
    }
};