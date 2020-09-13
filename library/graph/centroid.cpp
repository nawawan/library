#include <iostream>
#include <vector>
using namespace std;
//木の重心を配列に格納する関数
int n;
vector<vector<int>> G;
vector<int> used;
vector<int> cen;
void dfs(int s, int pre){
    used[s] = 1;
    bool flag = true;
    for(int j: G[s]){
        if(j != pre){
            dfs(j, s);
            if(used[j] > n / 2) flag = false;
            used[s] += used[j];
        }
    }
    if(n - used[s] > n / 2) flag = false;
    if(flag) cen.push_back(s);
}