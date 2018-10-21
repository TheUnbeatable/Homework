#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <queue>
#include <vector>
#include <string>
#include <bitset>
#define CLR(x) memset(x, 0, sizeof x)
#define FOR(i, v) for (vector <int> :: iterator i = v.begin(); i != v.end(); i ++)
using namespace std;

const int N = 33;
const int mod = 1e9 + 7;
const int dx[] = { 0, 0, 1, -1, 1, 1, -1, -1 };
const int dy[] = { 1, -1, 0, 0, 1, -1, 1, -1 };

struct edge { int nxt, to; };

class OneBlack {
private:
  edge e[N * N * 4];
  int fir[N * N], cntEdge, deg[N * N];
  int n, m, id[N][N], dp[N * N], s, t;
  bool vis[N][N], sv[N][N], tv[N][N];
  bool can[N][N];
  bitset <N * N> G[N * N];
  vector <int> in[N * N], out[N * N];
  
  inline void Dfs(int x, int y, int d) {
    if (vis[x][y] || !can[x][y]) return; vis[x][y] = 1;
    if (0 <= x + d && x + d < n) Dfs(x + d, y, d);
    if (0 <= y + d && y + d < m) Dfs(x, y + d, d);
  }
  inline void addedge(int x, int y) {
    if (G[x][y] || x == y) return; G[x][y] = 1; deg[y] ++;
    e[++ cntEdge] = (edge) { fir[x], y }; fir[x] = cntEdge;
  }
  inline void Mark(int x, int y, int col) {
    if (id[x][y]) return;
    id[x][y] = col;
    for (int i = 0, nx, ny; i < 8; i ++) {
      nx = x + dx[i]; ny = y + dy[i];
      if (nx < 0 || nx >= n) continue;
      if (ny < 0 || ny >= m) continue;
      if (!id[nx][ny] && !can[nx][ny]) Mark(nx, ny, col);
    }
  }
  inline void Add(int &x, int y) {
    if ((x += y) >= mod) x -= mod;
  }
public:
  inline int countColorings(vector <string> grid) {
    n = grid.size(); m = grid[0].length();
    CLR(dp); CLR(can); CLR(id); CLR(deg);
    for (int i = 0; i < n; i ++)
      for (int j = 0; j < m; j ++)
        if (grid[i][j] != '#') can[i][j] = 1;
    CLR(vis); Dfs(0, 0, 1);
    memcpy(sv, vis, sizeof vis);
    CLR(vis); Dfs(n - 1, m - 1, - 1);
    memcpy(tv, vis, sizeof vis);
    int del = 1;
    for (int i = 0; i < n; i ++)
      for (int j = 0; j < m; j ++)
        if (!sv[i][j] || !tv[i][j]) {
          can[i][j] = 0;
          if (grid[i][j] != '#') Add(del, del);
        }
    cntEdge = 0;
    int tot = 0;
    for (int i = 0; i < n; i ++)
      for (int j = 0; j < m; j ++)
        if (!can[i][j]) {
          if (!id[i][j]) Mark(i, j, ++ tot);
        }
        else id[i][j] = ++ tot;
    s = ++ tot; t = ++ tot;
    for (int i = 0; i < n; i ++)
      for (int j = 0; j < m; j ++) {
        if (i == n - 1 || j == 0) {
          if (can[i][j]) addedge(s, id[i][j]);
          else in[id[i][j]].push_back(s);
        }
        if (i == 0 || j == m - 1) {
          if (can[i][j]) addedge(id[i][j], t);
          else out[id[i][j]].push_back(t);
        }
        if (i && can[i][j] != can[i - 1][j]) {
          if (can[i][j]) in[id[i - 1][j]].push_back(id[i][j]);
          else out[id[i][j]].push_back(id[i - 1][j]);
        }
        if (j + 1 < m && can[i][j] != can[i][j + 1]) {
          if (can[i][j]) in[id[i][j + 1]].push_back(id[i][j]);
          else out[id[i][j]].push_back(id[i][j + 1]);
        }
        if (i && j + 1 < m) {
          if (can[i][j] && can[i - 1][j + 1]) addedge(id[i][j], id[i - 1][j + 1]);
          else if (can[i][j]) in[id[i - 1][j + 1]].push_back(id[i][j]);
          else out[id[i][j]].push_back(id[i - 1][j + 1]);
        }
      }
    for (int i = 1; i <= tot; i ++)
      FOR(a, in[i]) FOR(b, out[i]) addedge(*a, *b);
    queue <int> Q; Q.push(s); dp[s] = 1;
    while (Q.size()) {
      int x = Q.front(); Q.pop();
      for (int i = fir[x]; i; i = e[i].nxt) {
        deg[e[i].to] --;
        Add(dp[e[i].to], dp[x]);
        if (!deg[e[i].to]) Q.push(e[i].to);
      }
    }
    return (int)(1ll * dp[t] * del % mod);
  }
};
