#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;
vector<int> a, x;
int K;
//全ての山に対してgrundy数のXORを取れば後はNimと同じ
vector<int> grundy(vector<int> &a, vector<int> &x, int K){
    int mx = *max_element(x.begin(), x.end());
    vector<int> gr(mx + 1, 0);
    for(int i = 1; i <= mx; i++){
        set<int> s;
        for(int j = 0; j < K; j++){
            if(a[j] <= i) s.insert(gr[i - a[j]]);
        }
        int res = 0;
        while(s.count(res)) res++;
        gr[i] = res; 
    }
    return gr;
}

//分裂する時は分裂先のgrundy数のXORを取れば良い
//メモ化再帰で s.insert(grundy(hoge - i) ^ grundy(hoge - j));
//ってやればOK