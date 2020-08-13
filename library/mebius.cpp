#include <vector>
#include <map>
using namespace std;
//メビウス関数を返す
map<long long, long long> mebi(long long n){
    map<long long, long long> res;
    vector<long long> p;
    for(long long i = 2; i * i <= n; i++){
        if(n % i == 0){
            p.push_back(i);
            while(n % i == 0) n /= i;
        }
    }
    if(n != 1) p.push_back(n);
    int m = p.size();
    for(int bit = 0; bit < (1 << m); bit++){
        long long temp = 1, d = 1;
        for(int j = 0; j < m; j++){
            if(bit & (1 << j)){
                temp *= -1;
                d *= p[j];
            }
        }
        res[d] = temp;
    }
    return res;
}