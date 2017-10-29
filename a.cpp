#include <cstdio>
#include <iostream>
#include <set>
using namespace std;

typedef long long LL;
const int N = 2e5 + 5;
const LL mod = 1e9 + 7;

namespace MathCal {
  LL fac[N], inv[N];
  inline LL C(int x, int y) {
    if (x < y) return 0;
    return fac[x] * inv[y] % mod * inv[x - y] % mod;
  }
  inline LL pow(LL x, LL exp) {
    LL ret = 1;
    for (; exp; exp >>= 1, x = x * x % mod)
      if (exp & 1) ret = ret * x % mod;
    return ret;
  }
  inline void pre() {
    for (int i = fac[0] = 1; i < N; i ++) fac[i] = fac[i - 1] * i % mod;
    inv[N - 1] = pow(fac[N - 1], mod - 2);
    for (int i = N - 1; i >= 1; i --) inv[i - 1] = inv[i] * i % mod;
  }
}
using namespace MathCal;

struct edge {
  int nxt, to, id;
} e[N << 1];
int fir[N], cnt = 0, lst[N];
bool vis[N], cycle[N], found = 0;

int n, x[N], y[N], con[N];
set <int> X[N], Y[N];

inline void add(int x, int y, int id) {
  e[++ cnt] = (edge){fir[x], y, id};
  fir[x] = cnt;
}

inline void dfs(int x) {
  if (found) return;
  vis[x] = 1;
  for (int i = fir[x]; i; i = e[i].nxt) {
    if (e[i].to == lst[x]) continue;
    if (vis[e[i].to]) {
      found = 1;
      for (int p = x; p != e[i].to; p = lst[p]) cycle[p] = 1;
      cycle[p] = 1;
      break;
    }
    else {
      lst[e[i].to] = x;
      dfs(e[i].to);
    }
  }
}

inline void Assign(int x, int pa) {
  for (int i = fir[x]; i; i = e[i].to)
    if (!cycle[e[i].to] && e[i].to != pa) {
      con[e[i].id] = e[i].to;
      Assign(e[i].to);
    }
}

int main() {
  pre();
  scanf("%d", &n);
  for (int i = 1; i <= n + n; i ++) {
    scanf("%d%d", &x[i], &y[i]);
    add(x[i], y[i] + n, i);
    add(y[i] + n, x[i], i);
    X[x[i]].insert(y[i]);
    Y[y[i]].insert(x[i]);
  }
  for (int i = (n << 1); i; i --)
    if (!fir[i]) return !puts("0");
  dfs(1);
  for (int i = (n << 1); i; i --)
    if (cycle[i]) Assign(i, 0);
  return 0;
}
