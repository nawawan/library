#include <iostream>
#include <vector>
using namespace std;
//木の重心を配列に格納する関数
//初めcenは空
//usedは部分木のサイズ
//Gは隣接リスト
//nはノード数
void dfs(int &n, int s, int pre, vector<int>&cen, vector<int>&used, vector<vector<int>>&G){
    used[s] = 1;
    bool flag = true;
    for(int j: G[s]){
        if(j != pre){
            dfs(n, j, s, cen, used, G);
            if(used[j] > n / 2) flag = false;
            used[s] += used[j];
        }
    }
    if(n - used[s] > n / 2) flag = false;
    if(flag) cen.push_back(s);
}