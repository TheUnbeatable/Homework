#include <bits/stdc++.h>
using namespace std;

const int N = 430;
const int M = 200 * 200 * 4;
const int S = N - 1, T = N - 2;

struct edge {
  int nxt, to, cap;
} e[M];
int fir[N], cnt = 1;
int dis[N], swp[N];

inline void addedge(int x, int y, int c, int _c = 0) {
  if (c == 0) return;
  e[++ cnt] = (edge) { fir[x], y, c }; fir[x] = cnt;
  e[++ cnt] = (edge) { fir[y], x, _c }; fir[y] = cnt;
}

inline int Bfs() {
  memset(dis, -1, sizeof dis);
  memcpy(fir, swp, sizeof fir);
  dis[T] = 0;
  static queue <int> Q;
  Q.push(T);
  while (Q.size()) {
    int x = Q.front(); Q.pop();
    for (int i = fir[x]; i; i = e[i].nxt)
      if (dis[e[i].to] == -1 && e[i ^ 1].cap > 0) {
        dis[e[i].to] = dis[x] + 1;
        Q.push(e[i].to);
      }
  }
  return dis[S];
}

inline int Dfs(int x, int flow) {
  if (!flow || x == T) return flow;
  int res = 0;
  for (int &i = fir[x]; i; i = e[i].nxt)
    if (e[i].cap && dis[e[i].to] == dis[x] - 1) {
      int t = Dfs(e[i].to, min(flow, e[i].cap));
      flow -= t; res += t;
      e[i].cap -= t; e[i ^ 1].cap += t;
      if (!flow) return res;
    }
  dis[x] = -1;
  return res;
}

inline int maxflow() {
  int ans = 0;
  while (~ Bfs()) ans += Dfs(S, 1 << 29);
  return ans;
}

int n, m, u[N], v[N];

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n + m; i ++) scanf("%d", &u[i]);
  for (int i = 1; i <= n + m; i ++) scanf("%d", &v[i]);
  int ans = 0;
  for (int i = 1, t; i <= n; i ++) {
    t = max(u[i], v[i]); ans += t;
    addedge(S, i, t - u[i]);
    addedge(i, T, t - v[i]);
  }
  for (int i = n + 1, t; i <= n + m; i ++) {
    t = max(u[i], v[i]); ans += t;
    addedge(S, i, t - v[i]);
    addedge(i, T, t - u[i]);
  }
  for (int i = 1, c; i <= n; i ++)
    for (int j = 1; j <= m; j ++) {
      scanf("%d", &c); addedge(i, n + j, c, c);
    }
  memcpy(swp, fir, sizeof swp);
  printf("%d\n", ans - maxflow());
  for (int i = 1; i <= n + m; i ++) {
    if (dis[i] == -1) printf("%d ", (i <= n) + 1);
    else printf("%d ", (i > n) + 1);
  }
  puts("");
  return 0;
}
