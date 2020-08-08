#include <iostream>
#include <vector>
using namespace std;
struct BIT{
    vector<long long> num;
    int N;
    BIT(int n){
        N = n;
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
        while(ind <= N){
            num[ind] += t;
            ind += ind & -ind;
        }
    }
};