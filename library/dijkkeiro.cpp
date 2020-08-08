#include <bits/stdc++.h>
using namespace std;
struct edge{
    int to;
    int cost;
};
typedef pair<int, int> P;//firstは最短距離、secondは頂点番号
long long INF = 1e14;
int N, M;//Vは頂点、Eは辺の数

void solve(){//priority_queueを用いる
    int prev[N];//経路復元用
    fill(prev, prev + N, -1);
    vector <edge> G[N];
    int d[N];//各頂点までの距離
    priority_queue<P, vector<P>, greater<P>> que;
    fill(d, d + N, INF);
    for(int i = 0; i < M; i++){
        int a = 0;
        edge es;
        cin >> a >> es.to >> es.cost;
        G[a].push_back(es);
    }
    int s = 0;//スタート地点は最初0
    d[s] = 0;
    que.push(P(0, 0));
    while(!que.empty()){
        P p = que.top();
        que.pop();
        int v = p.second;
        if(d[v] < p.first) continue;
        for(int i = 0; i < G[v].size(); i++){
            edge e = G[v][i];
            if(d[e.to] > d[v] + e.cost){
                d[e.to] = d[v] + e.cost;
                que.push(P(d[e.to], e.to));
                prev[e.to] = v;
            }
        }
    }
    int t = N - 1;//ゴールから辿っていく
    vector<int> path;
    for(; t != -1; t = prev[t]) path.push_back(t);
    reverse(path.begin(), path.end());//このままだと終点→始点なので逆にする
    cout << path[0] << endl;//pathはポインタではないから書き換える必要あり
}