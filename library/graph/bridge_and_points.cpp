#include <vector>
#include <utility>
#include <algorithm>
using namespace std;
struct lowlinks{
    vector<int> order;
    vector<int> low;
    vector<pair<int, int>> bridge;//橋
    vector<int> points;//関節点
    lowlinks(vector<vector<int>>&G){
        int sz = G.size();
        order.resize(sz, -1);
        low.resize(sz);
        dfs(0, 0, -1, G);
        sort(points.begin(), points.end());
        sort(bridge.begin(), bridge.end());
    }
    void dfs(int now, int num, int par, vector<vector<int>>&G){
        order[now] = low[now] = num;
        ++num;
        bool f = false;
        int cnt = 0;
        for(int t: G[now]){
            if(order[t] == -1){
                dfs(t, num, now, G);
                low[now] = min(low[now], low[t]);
                if(now != 0 && order[now] <= low[t]) f = true;
                ++cnt;
            }
            else if(t != par){
                low[now] = min(low[now], order[t]);
            }
            if(order[now] < low[t]){
                bridge.push_back({min(now, t), max(now, t)});
            }
        }
        if(now == 0 && cnt > 1) f = true;
        if(f) points.push_back(now);
    }
};