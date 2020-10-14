#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;
//ここではダブリングで実装している
vector<int> SuffixArray(string S){
    int N = (int)S.size();
    vector<int> rank(N + 1), temp(N + 1), sa(N + 1);
    for(int i = 0; i <= N; i++){
        sa[i] = i;
        rank[i] = i < N ? (int)S[i] : -1;
    }
    for(int k = 1; k <= N; k *= 2){//ダブリング開始
        auto comp = [&](int i, int j){
            if(rank[i] != rank[j]) return rank[i] < rank[j];
            else{
                int ni = i + k <= N ? rank[i + k] : -1;
                int nj = j + k <= N ? rank[j + k] : -1;//ダブリングで後ろに付け加えたもの同士の比較
                return ni < nj;
            }
        };
        sort(sa.begin(), sa.end(), comp);
        temp[sa[0]] = 0;
        for(int i = 1; i <= N; i++){
            temp[sa[i]] = temp[sa[i - 1]] + (comp(sa[i - 1], sa[i]) ? 1 : 0);//あっても ==の場合の時のfalseなので必ずソートされている
        }
        swap(temp, rank);
    }
    return sa;
}
bool judge(string S, string T, vector<int> sa){//SにTが含まれているか
    int left = 0, right = S.size();//二分探索で判定
    int Tlen = T.size();
    while(right - left > 1){
        int mid = (right + left) / 2;
        if(S.compare(sa[mid], Tlen, T) < 0) left = mid;
        else right = mid;
    }
    return S.compare(sa[right], Tlen, T) == 0;
}

vector<int> LCP(string S, vector<int> sa){
    int N = (int)S.size();
    vector<int> rank(N + 1), lcp(N + 1, 0);
    for(int i = 0; i <= N; i++) rank[sa[i]] = i;
    int h = 0;
    lcp[0] = 0;
    for(int i = 0; i < N; i++){
        if(rank[i] == 0) continue;
        int j = sa[rank[i] - 1];
        if(h > 0) h--;
        while(i + h < N && j + h < N){
            if(S[i + h] != S[j + h]) break;
            h++;
        }
        lcp[rank[i] - 1] = h;
    }
    return lcp;
}