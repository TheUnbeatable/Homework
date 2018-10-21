#include <cstdio>
#include <iostream>
#include <map>
#define travel(x, i) for (int i = fir[x]; i; i = e[i].nxt)
#define Travel(x, i) for (int i = Fir[x]; i; i = E[i].nxt)
using namespace std;

typedef long long LL;
const int N = 2e5 + 5;
const LL mod = 1e9 + 7;

template <typename T> inline void Read(T &x) {
  char ch; x = 0;
  while (!isdigit(ch = getchar()));
  do {x = (x << 1) + (x << 3) + ch - '0';} while (isdigit(ch = getchar()));
}

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
int fir[N], cnt = 0, lst[N], deg[N], size[N], rt;

struct Edge {
  int nxt, to;
} E[N << 1];
int Fir[N], Cnt = 0;

bool vis[N], cycle[N], found = 0;
int n, x[N], y[N], con[N];
map <int, int> X[N], Y[N];
int vertex[N], point[N], top, tp;

inline void add(int x, int y, int id) {
  e[++ cnt] = (edge){fir[x], y, id};
  fir[x] = cnt;
}

inline void Add(int x, int y) {
  E[++ Cnt] = (Edge){Fir[x], y};
  Fir[x] = Cnt;
}

inline void dfs(int x) {
  vis[x] = 1;
  vertex[++ top] = x;
  travel(x, i) {
    if (e[i].to == lst[x]) continue;
    if (!found || !vis[e[i].to]) point[++ tp] = e[i].id;
    if (!found && vis[e[i].to]) {
      found = 1;
      rt = x;
      for (int p = x; p != e[i].to; p = lst[p]) cycle[p] = 1;
      cycle[e[i].to] = 1;
    }
    else if (!vis[e[i].to]) {
      lst[e[i].to] = x;
      dfs(e[i].to);
    }
  }
}

inline void Assign(int x, int pa) {
  travel(x, i)
    if (!cycle[e[i].to] && e[i].to != pa) {
      con[e[i].id] = e[i].to;
      Assign(e[i].to, x);
    }
}

inline void Assign_Cycle(int x, int pre, bool pattern) {
  travel(x, i)
    if (cycle[e[i].to] && pre != e[i].to) {
      if (pattern) con[e[i].id] = x;
      else con[e[i].id] = e[i].to;
      if (x != rt || !pre) Assign_Cycle(e[i].to, x, pattern);
      break;
    }
}

inline void Build() {
  for (int i = 1; i <= tp; i ++)
    Fir[point[i]] = deg[point[i]] = 0;
  Cnt = 0;
  map <int, int> :: iterator it;
  for (int u = tp, i; u; u --) {
    i = point[u];
    if (con[i] <= n) {
      it = X[x[i]].find(y[i]);
      while (it != X[x[i]].begin()) {
	it --;
	deg[it -> second] ++;
	Add(i, it -> second);
      }
    }
    else {
      it = Y[y[i]].find(x[i]);
      while (it != Y[y[i]].begin()) {
	it --;
	deg[it -> second] ++;
	Add(i, it -> second);
      }
    }
  }
}

inline void Get_Size(int x, int pa) {
  size[x] = 1;
  Travel(x, i) {
    Get_Size(E[i].to, x);
    size[x] += size[E[i].to];
  }
}

inline LL Calc(int x, int pa) {
  int p = size[x] - 1;
  LL res = 1;
  Travel(x, i) {
    res = res * Calc(E[i].to, x) % mod * C(p, size[E[i].to]) % mod;
    p -= size[E[i].to];
  }
  return res;
}

inline LL Solve() {
  LL res = 1;
  int tot = top;
  Build();
  for (int u = tp, i = point[u]; u; u --, i = point[u])
    if (!deg[i]) {
      Get_Size(i, 0);
      res = res * Calc(i, 0) % mod * C(tot, size[i]) % mod;
      tot -= size[i];
    }
  return res;
}

int main() {
  pre();
  Read(n);
  for (int i = 1; i <= (n << 1); i ++) {
    Read(x[i]); Read(y[i]);
    add(x[i], y[i] + n, i);
    add(y[i] + n, x[i], i);
    X[x[i]][y[i]] = i;
    Y[y[i]][x[i]] = i;
  }
  for (int i = (n << 1); i; i --)
    if (!fir[i]) return !puts("0");
  LL ans = 1, tmp;
  int p = n << 1;
  for (int k = 1; k <= (n << 1); k ++)
    if (!vis[k]) {
      found = 0;
      tp = rt = top = 0;
      dfs(k);
      if (!rt) return !puts("0");
      for (int i = top; i; i --)
	if (cycle[vertex[i]]) Assign(vertex[i], 0);
      Assign_Cycle(rt, 0, 0);
      tmp = Solve();
      Assign_Cycle(rt, 0, 1);
      tmp += Solve();
      if (tmp >= mod) tmp -= mod;
      ans = ans * tmp % mod * C(p, top) % mod;
      p -= top;
    }
  printf("%lld\n", ans);
  return 0;
}
