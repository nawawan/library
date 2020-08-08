#include <bits/stdc++.h>
using namespace std;
//以下雛形を記す
int N, M, s, t;//Vは頂点、Kは辺の数 sは始点、tは終点
long long INF =  100000000;
struct edge{
    int from;
    int to;
    int cost;
};

void solve(){
    vector<edge> es(M);
    vector<int> d(N);//各頂点までの距離
    for(int i = 0; i < M; i++) d[i] = INF;
    d[s] = 0;
    int k = 0;
    while(true){
        bool flag = false;
        for(int i = 0; i < M; i++){
            edge e = es[i];
            if(d[e.from] != INF && d[e.to] > d[e.from] + e.cost){
                d[e.to] = d[e.from] + e.cost;
                flag = true;
                if(e.to == t) flag == true;
            }
        }
        if(!flag) break;
        if(k == N && flag){//閉路があって無限に更新される場合はinf
            cout << "inf" << endl;
            return;
        }
    }
    cout << d[t] << endl;
}