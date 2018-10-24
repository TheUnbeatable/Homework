#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;

const int N = 33, M = N * N * 2;
const int S = M - 1, T = M - 2;
const int SS = M - 3, TT = M - 4;

int ans = 0;

namespace Flow {
  struct edge {
    int nxt, to, cap, cost;
  } e[M * 50];
  int fir[M], cnt = 1;
  int dis[M];
  bool vis[M], inq[M];

  inline void Init() {
    memset(fir, 0, sizeof fir); cnt = 1;
  }
  inline void connect(int x, int y, int c, int w) {
    e[++ cnt] = (edge) { fir[x], y, c, w }; fir[x] = cnt;
    e[++ cnt] = (edge) { fir[y], x, 0, -w }; fir[y] = cnt;
  }
  inline void addedge(int x, int y, int c, int w) {
    if (w <= 0) connect(x, y, c, w);
    else {
      ans += c * w;
      connect(y, x, c, -w);
      connect(S, y, c, 0);
      connect(x, T, c, 0);
    }
  }
  inline int SPFA(int s, int t) {
    queue <int> Q;
    memset(dis, -0x3f, sizeof dis);
    Q.push(s); dis[s] = 0;
    while (Q.size()) {
      int x = Q.front(); Q.pop(); inq[x] = 0;
      for (int i = fir[x]; i; i = e[i].nxt)
        if (e[i].cap && dis[e[i].to] < dis[x] + e[i].cost) {
          dis[e[i].to] = dis[x] + e[i].cost;
          if (!inq[e[i].to]) {
            Q.push(e[i].to); inq[e[i].to] = 1;
          }
        }
    }
    return dis[t];
  }
  inline int Dfs(int x, int t, int flow) {
    if (x == t || !flow) return flow;
    int res = 0;
    vis[x] = 1;
    for (int i = fir[x]; i; i = e[i].nxt)
      if (!vis[e[i].to]
          && e[i].cap
          && dis[e[i].to] == dis[x] + e[i].cost) {
        int tmp = Dfs(e[i].to, t, min(flow, e[i].cap));
        flow -= tmp; res += tmp;
        e[i].cap -= tmp; e[i ^ 1].cap += tmp;
        if (!flow) break;
      }
    vis[x] = 0;
    if (flow) dis[x] = - 2e9;
    return res;
  }
  inline pair <int, int> minCost(int s, int t) {
    int res = 0, su = 0, d, f;
    while ((d = SPFA(s, t)) >= - 1e9) {
      f = Dfs(s, t, 1 << 30);
      su += f;
      res += f * d;
    }
    return make_pair(su, res);
  }
}
using Flow :: e;
using Flow :: fir;
using Flow :: addedge;
using Flow :: minCost;

bool forced[N][N];
int n, m, id[N][N][2], clo;

int main() {
  int Case;
  scanf("%d", &Case);
  for (int w = 1; w <= Case; w ++) {
    ans = 0;
    Flow :: Init();
    scanf("%d%d", &n, &m);
    clo = 0;
    for (int i = 1; i <= n; i ++)
      for (int j = 1; j <= m; j ++) {
        id[i][j][0] = ++ clo;
        id[i][j][1] = ++ clo;
      }
    for (int i = 1, w, t; i <= n; i ++)
      for (int j = 1; j < m; j ++) {
        // benefit between **columns**
        scanf("%d", &w);
        t = (i + j) & 1;
        if (t) addedge(id[i][j][1], id[i][j + 1][0], 1, w);
        else addedge(id[i][j + 1][1], id[i][j][0], 1, w);
      }
    for (int i = 1, w, t; i < n; i ++)
      for (int j = 1; j <= m; j ++) {
        // benefit between **rows**
        scanf("%d", &w);
        t = (i + j) & 1;
        if (!t) addedge(id[i][j][1], id[i + 1][j][0], 1, w);
        else addedge(id[i + 1][j][1], id[i][j][0], 1, w);
      }
    memset(forced, 0, sizeof forced);
    int E;
    scanf("%d", &E);
    for (int i = 1, x, y; i <= E; i ++) {
      scanf("%d%d", &x, &y); forced[x][y] = 1;
    }
    for (int i = 1; i <= n; i ++)
      for (int j = 1; j <= m; j ++)
        if (forced[i][j]) {
          addedge(SS, id[i][j][1], 1, 0);
          addedge(id[i][j][0], TT, 1, 0);
        }
        else addedge(id[i][j][0], id[i][j][1], 1, 0);
    pair <int, int> res = minCost(S, T);
    ans += res.second;
    for (int i = fir[S]; i; i = e[i].nxt)
      e[i].cap = e[i ^ 1].cap = 0;
    for (int i = fir[T]; i; i = e[i].nxt)
      e[i].cap = e[i ^ 1].cap = 0;
    res = minCost(SS, TT);
    if (res.first == E) printf("Case #%d: %d\n", w, res.second + ans);
    else printf("Case #%d: Impossible\n", w);
  }
  return 0;
}
