#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
const int N = 300, M = 1e4 + 50;
const int S = N - 1, T = N - 2;

namespace CostFlow {
#define travel(x, i) for (int i = fir[x]; i; i = e[i].nxt)
  struct edge {
    int nxt, to, cap;
    LL len;
  } e[N * N * 4];
  int fir[N], lst[N], cnt = 1;
  LL dis[N];
  bool inq[N], vis[N];
  
  inline void addedge(int x, int y, int c, LL l) {
    if (!x || !y || !c || x == y) return;
    e[++ cnt] = (edge) { fir[x], y, c, l }; fir[x] = cnt;
    e[++ cnt] = (edge) { fir[y], x, 0, -l }; fir[y] = cnt;
  }
  inline LL SPFA(int s, int t) {
    memset(dis, 0x3f, sizeof dis);
    memcpy(lst, fir, sizeof fir);
    queue <int> Q;
    Q.push(s); dis[s] = 0;
    while (Q.size()) {
      int x = Q.front(); Q.pop();
      inq[x] = 0;
      travel(x, i)
        if (e[i].cap && dis[x] + e[i].len < dis[e[i].to]) {
          dis[e[i].to] = dis[x] + e[i].len;
          if (!inq[e[i].to]) {
            Q.push(e[i].to); inq[e[i].to] = 1;
          }
        }
    }
    return dis[t];
  }
  inline LL Dfs(int x, int t, int flow) {
    if (!flow || x == t) return flow;
    vis[x] = 1;
    int res = 0;
    for (int &i = lst[x]; i; i = e[i].nxt)
      if (!vis[e[i].to] && e[i].cap && dis[e[i].to] == dis[x] + e[i].len) {
        int tmp = Dfs( e[i].to, t, min(flow, e[i].cap) );
        flow -= tmp; res += tmp;
        e[i].cap -= tmp; e[i ^ 1].cap += tmp;
        if (!flow) break;
      }
    vis[x] = 0;
    if (!res) dis[x] = 1e18;
    return res;
  }
  inline LL minCost(int s, int t) {
    LL res = 0, dis;
    while ((dis = SPFA(s, t)) < 1e14)
      res += dis * Dfs(s, t, 1 << 29);
    return res;
  }
}
using CostFlow :: addedge;
using CostFlow :: minCost;

int C, D, n, x[M], y[M];
vector <pair <int, int> > mo[200];

inline void generate(int *x) {
  int z, a, b, p;
  scanf("%d%d%d%d", &z, &a, &b, &p);
  x[1] = z;
  for (int i = 2; i <= n; i ++)
    x[i] = (1ll * x[i - 1] * a + b) % p;
}

inline LL mabs(LL x) {
  return x > 0 ? x : - x;
}

inline LL calc(int a, int b) {
  static int wnum[M];
  int top = 0;
  int t = (a + b) / 2;
  for (auto p : mo[a]) {
    int f = t + (p.first - a);
    wnum[++ top] = f - p.second;
    if (a == 0 && b == 3) {
      cerr << "!!! " << f << " " << p.second << endl;
    }
  }
  t += C;
  for (auto p : mo[b]) {
    int f = t + (p.first - b);
    wnum[++ top] = - (f - p.second);
  }
  sort(wnum + 1, wnum + top + 1);
  int val = wnum[(1 + top) >> 1];
  int co = val / C;
  LL ans = 1e18;
  for (int i = co - 1; i <= co + 1; i ++) {
    LL res = 0, x = i * C;
    for (int j = 1; j <= top; j ++) res += mabs(x - wnum[j]);
    ans = min(ans, res);
  }
  return ans;
}

int main() {
  freopen("wang.in", "r", stdin);
  freopen("wang.out", "w", stdout);
  scanf("%d%d", &C, &n);
  D = 2 * C;
  generate(x); generate(y);
  for (int i = 1; i <= n; i ++)
    mo[x[i] % D].push_back(make_pair(x[i], y[i]));
  for (int i = 0; i < D; i += 2) {
    addedge(S, i + 1, 1, 0);
    for (int j = 1; j < D; j += 2)
      addedge(i + 1, j + 1, 1, calc(i, j));
  }
  for (int j = 1; j < D; j += 2)
    addedge(j + 1, T, 1, 0);
  printf("%lld\n", minCost(S, T));
  return 0;
}
