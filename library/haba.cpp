#include <bits/stdc++.h>
using namespace std;

int main(){
  int R, C, sx, sy, gx, gy;
  cin >> R >> C >> sx >> sy >> gx >> gy;
  vector<vector<char>> lab(R, vector<char>(C));
  vector<vector<int>> ans(R, vector<int>(C));
  vector<int> dx = {-1, 0, 1, 0};
  vector<int> dy = {0, -1, 0, 1};
  for(int i = 0; i < R; i++){
    for(int j = 0; j < C; j++){
      cin >> lab.at(i).at(j);
      ans.at(i).at(j) = -1;
    }
  }
  ans.at(sx - 1).at(sy - 1) = 0;
  typedef pair<int, int> P;
  queue<P> Q;
  P a = make_pair(sx - 1, sy - 1);
  Q.push(a);
  lab.at(sx - 1).at(sy - 1) = '#';
  while(!Q.empty()){
    P p = Q.front();
    for(int i = 0; i < 4; i++){
      int nx = p.first, ny = p.second;
      nx += dx.at(i);
      ny += dy.at(i);
      if(0 <= nx && nx < R && 0 <= ny && ny < C && lab.at(nx).at(ny) == '.'){
        P b = make_pair(nx, ny);
        Q.push(b);
        ans.at(nx).at(ny) = ans.at(p.first).at(p.second) + 1;
        lab.at(nx).at(ny) = '#';
      }
    }
    Q.pop();
  }
  cout << ans.at(gx - 1).at(gy - 1) << endl;
}
