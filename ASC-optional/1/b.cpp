#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;

const int N = 230;
const int S = N - 1, T = N - 2;

int n, m, lft[N * N];

namespace Flow {
  struct edge {
    int nxt, to, cap;
  } e[3000000];
  int fir[N], lst[N], dis[N], cnt = 1;

  inline void Init() {
    cnt = 1;
    memset(fir, 0, sizeof fir);
  }
  inline void addedge(int x, int y, int c) {
    e[++ cnt] = (edge) { fir[x], y, c }; fir[x] = cnt;
    e[++ cnt] = (edge) { fir[y], x, 0 }; fir[y] = cnt;
  }
  inline int Bfs(int s, int t) {
    queue <int> Q;
    memset(dis, -1, sizeof dis);
    memcpy(lst, fir, sizeof fir);
    dis[s] = 0; Q.push(s);
    while (!Q.empty()) {
      int x = Q.front(); Q.pop();
      for (int i = fir[x]; i; i = e[i].nxt)
        if (e[i].cap && dis[e[i].to] == -1) {
          Q.push(e[i].to);
          dis[e[i].to] = dis[x] + 1;
        }
    }
    return dis[t];
  }
  inline int Dfs(int x, int flow) {
    if (x == T) return flow;
    int res = 0;
    for (int &i = lst[x]; i; i = e[i].nxt)
      if (e[i].cap && dis[e[i].to] == dis[x] + 1) {
        int d = Dfs(e[i].to, min(flow, e[i].cap));
        flow -= d; res += d;
        e[i].cap -= d; e[i ^ 1].cap += d;
        if (!flow) break;
      }
    if (!res) dis[x] = 1e9;
    return res;
  }
  inline int Maxflow() {
    int res = 0;
    while (~ Bfs(S, T)) res += Dfs(S, (int)1e9);
    return res;
  }
  inline void Solve() {
    Maxflow();
    for (int i = fir[S]; i; i = e[i].nxt)
      if (e[i].cap) return (void) puts("NO");
    puts("YES");
    for (int i = 1; i <= m; i ++)
      printf("%d\n", :: lft[i] + e[i << 1 | 1].cap);
  }
}
using Flow :: addedge;

int in[N];

int main() {
#ifdef ONLINE_JUDGE
  freopen("cooling.in", "r", stdin);
  freopen("cooling.out", "w", stdout);
#endif
  scanf("%d%d", &n, &m);
  for (int i = 1, u, v, l, r; i <= m; i ++) {
    scanf("%d%d%d%d", &u, &v, &l, &r);
    lft[i] = l;
    addedge(u, v, r - l);
    in[v] += l; in[u] -= l;
  }
  for (int i = 1; i <= n; i ++)
    if (in[i] > 0) addedge(S, i, in[i]);
    else if (in[i] < 0) addedge(i, T, - in[i]);
  Flow :: Solve();
  return 0;
}
