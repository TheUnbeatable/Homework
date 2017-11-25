#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>
#define travel(x, i) for (int i = fir[x]; i; i = e[i].nxt)
#define rep(i, x, y) for (int i = (x); i <= (y); i ++)
using namespace std;

typedef long long LL;
const int N = 1e5 + 10;

struct edge {
  int nxt, to;
} e[N << 1];
int fir[N], cnt = 0;
int n, m, w[N], sum[N];

inline void addedge(int x, int y) {
  e[++ cnt] = (edge){fir[x], y};
  fir[x] = cnt;
}

namespace Tree {
  inline void Dfs(int x, int f) {
    if (x == 1) w[x] = 1;
    else w[x] = - w[f];
    sum[x] = w[x];
    travel(x, i)
      if (e[i].to != f) {
	Dfs(e[i].to, x);
	sum[x] += sum[e[i].to];
      }
  }
  inline void solve() {
    LL ans = 0;
    Dfs(1, 0);
    if (sum[1]) return (void) puts("-1");
    rep(i, 1, n) ans += abs(sum[i]);
    printf("%lld\n", ans);
  }
}

namespace Ring {
  bool vis[N], odd;
  int fa[N], num[N], u, v;
  
  inline void Dfs(int x, int f) {
    fa[x] = f;
    vis[x] = 1;
    if (x == 1) w[x] = 1;
    else w[x] = - w[f];
    sum[x] = w[x];
    travel(x, i)
      if (e[i].to != f) {
	if (!vis[e[i].to]) {
	  Dfs(e[i].to, x);
	  sum[x] += sum[e[i].to];
	}
	else {
	  u = x; v = e[i].to;
	  if (w[x] == w[e[i].to]) odd = 1;
	}
      }
  }
  inline void solve() {
    LL ans = 0;
    Dfs(1, 0);
    if (odd) {
      if (sum[1] & 1) return (void) puts("-1");
      int t = - (sum[1] >> 1);
      ans += abs(t);
      for (int i = u; i; i = fa[i]) sum[i] += t;
      for (int i = v; i; i = fa[i]) sum[i] += t;
      rep(i, 1, n) ans += abs(sum[i]);
      printf("%lld\n", ans);
    }
    else {
      if (sum[1]) return (void) puts("-1");
      memset(w, 0, sizeof w);
      for (int i = u; i; i = fa[i]) w[i] ++;
      for (int i = v; i; i = fa[i]) w[i] --;
      int t = 0, k;
      rep(i, 1, n) {
	if (w[i] == 0) ans += abs(sum[i]);
	else num[++ t] = sum[i] * w[i];
      }
      num[++ t] = 0;
      sort(num + 1, num + t + 1);
      k = num[(t + 1) >> 1];
      rep(i, 1, t) ans += abs(num[i] - k);
      printf("%lld\n", ans);
    }
  }
}

int main() {
  scanf("%d%d", &n, &m);
  int x, y;
  rep(i, 1, m) {
    scanf("%d%d", &x, &y);
    addedge(x, y); addedge(y, x);
  }
  if (m == n - 1) Tree :: solve();
  else Ring :: solve();
  return 0;
}
