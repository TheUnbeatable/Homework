#include <bits/stdc++.h>
using namespace std;

int n, m, ans;

namespace Flow {
  const int N = 1100, M = 1e4;
  const int S = N - 1, T = N - 2;
  struct edge {
    int nxt, to, cap;
  } e[M];
  int dis[N], fir[N], swp[N], cnt = 1;

  inline void addedge(int x, int y, int c) {
    e[++ cnt] = (edge) { fir[x], y, c }; fir[x] = cnt;
    e[++ cnt] = (edge) { fir[y], x, 0 }; fir[y] = cnt;
  }
  inline void build() {
    for (int i = 1, c; i <= :: n; i ++) {
      scanf("%d", &c);
      if (c > 0) {
        ans += c;
        addedge(S, i, c);
        addedge(i + n, T, c);
      }
      else if (c < 0)
        addedge(i, i + n, - c);
    }
    for (int i = 1, x, y; i <= :: m; i ++) {
      scanf("%d%d", &x, &y);
      addedge(x, y, 1 << 29);
      addedge(x + n, y + n, 1 << 29);
    }
    memcpy(swp, fir, sizeof swp);
  }
  inline int Bfs() {
    static queue <int> Q;
    memcpy(fir, swp, sizeof swp);
    memset(dis, -1, sizeof dis);
    Q.push(T); dis[T] = 1;
    while (Q.size()) {
      int x = Q.front(); Q.pop();
      for (int i = fir[x]; i; i = e[i].nxt)
        if (e[i ^ 1].cap && dis[e[i].to] == -1) {
          dis[e[i].to] = dis[x] + 1;
          Q.push(e[i].to);
        }
    }
    return dis[S];
  }
  inline int Dfs(int x, int flow) {
    if (x == T || !flow) return flow;
    int tot = 0;
    for (int &i = fir[x]; i; i = e[i].nxt)
      if (e[i].cap && dis[e[i].to] == dis[x] - 1) {
        int res = Dfs(e[i].to, min(flow, e[i].cap));
        e[i].cap -= res; e[i ^ 1].cap += res;
        tot += res; flow -= res;
        if (!flow) return tot;
      }
    dis[x] = -1;
    return tot;
  }
  inline int maxFlow() {
    int ans = 0;
    while (Bfs() != -1) ans += Dfs(S, 1 << 29);
    return ans;
  }
}

int main() {
  freopen("permutation.in", "r", stdin);
  freopen("permutation.out", "w", stdout);
  scanf("%d%d", &n, &m);
  Flow :: build();
  printf("%d\n", ans - Flow :: maxFlow());
  return 0;
}
