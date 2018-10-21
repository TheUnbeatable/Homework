#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

typedef long long LL;
const int N = 2e5 + 50;
const int M = 1e7;

LL ans[N], su;
bool vis[N], done[N];
int n, q, m, a[N], lc[N], rc[N], dep[N], id[N];
int fa[N], jmp[N][18], le[N], ri[N], clo;
int tim[N], rt[N];
  
struct Bit {
#define lb(x) (x & (- x))
  LL a[N];
  int vis[N], cur;
  Bit() {
    cur = 0; memset(vis, 0, sizeof vis);
  }
  inline void Init() { cur ++; }
  inline void Add(int p, int v) {
    if (p <= 0) return;
    for (; p < N; p += lb(p)) {
      if (vis[p] == cur) a[p] += v;
      else vis[p] = cur, a[p] = v;
    }
  }
  inline LL Sum(int p) {
    int res = 0;
    for (; p > 0; p -= lb(p))
      if (vis[p] == cur) res += a[p];
    return res;
  }
  inline void Add(int l, int r, int v) {
    Add(l, v); Add(r + 1, - v);
  }
  inline int Sum(int l, int r) {
    return Sum(r) - Sum(l - 1);
  }
} cntChild, cntPath;

namespace Seg {
#define mid ((L + R) >> 1)
  int lc[M], rc[M], Min[M], Max[M], Sz;
  inline int Merge(int x, int y) {
    if (!x && !y) return 0;
    int z = ++ Sz;
    Min[z] = min(Min[x], Min[y]);
    Max[z] = max(Max[x], Max[y]);
    if (!x || !y) {
      lc[z] = lc[x] + lc[y];
      rc[z] = rc[x] + rc[y];
    } else {
      lc[z] = Merge(lc[x], lc[y]);
      rc[z] = Merge(rc[x], rc[y]);
    }
    return z;
  }
  inline int Add(int x, int v, int L = 1, int R = q + 2) {
    int z = ++ Sz;
    Max[z] = max(Max[x], v);
    Min[z] = min(Min[x], v);
    lc[z] = rc[z] = 0;
    if (L == R) return z;
    if (v <= mid) {
      lc[z] = Add(lc[x], v, L, mid);
      rc[z] = rc[x];
    } else {
      lc[z] = lc[x];
      rc[z] = Add(rc[x], v, mid + 1, R);
    }
    return z;
  }
  inline int lower_bound(int x, int lb, int L = 1, int R = q + 2) {
    if (!x) return (int)1e9;
    if (L == R) return L;
    if (lb <= mid) {
      if (Max[lc[x]] >= lb)
        return lower_bound(lc[x], lb, L, mid);
      else return Min[rc[x]];
    }
    else return lower_bound(rc[x], lb, mid + 1, R);
  }
#undef mid
}

inline void Dfs(int x, int f) {
  if (!x) return;
  dep[x] = dep[f] + 1;
  fa[x] = jmp[x][0] = f;
  for (int i = 1; i < 18; i ++)
    f = jmp[x][i] = jmp[f][i - 1];
  le[x] = ++ clo;
  Dfs(lc[x], x); Dfs(rc[x], x);
  ri[x] = clo;
}

inline int Top(int x) {
  int k = cntPath.Sum(le[x]);
  if (k == cntPath.Sum(1)) return 0;
  for (int i = 17; ~ i; i --)
    if (jmp[x][i] && cntPath.Sum(le[jmp[x][i]]) == k) x = jmp[x][i];
  return x;
}

inline void Build(int x) {
  if (!x) return;
  Build(lc[x]); Build(rc[x]);
  rt[x] = Seg :: Merge(rt[lc[x]], rt[rc[x]]);
  rt[x] = Seg :: Add(rt[x], q + 2 - tim[x]);
}

inline bool check(int x, int y, int f, int stamp) {
  int tx = Seg :: lower_bound(rt[x], stamp + 1);
  int ty = Seg :: lower_bound(rt[y], stamp + 1);
  if (tx == 1e9 && ty == 1e9) return x == lc[f];
  return tx < ty;
}

inline void AddLeaf(int x) {
  int curt = q + 2 - tim[x];
  int f = fa[x], sx, sy, y, lf, rt;
  done[x] = 1;
  cntChild.Add( le[x], 1 );
  cntPath.Add( le[x], ri[x], 1 );
  while (x) {
    x = Top(x);
    if (!x) break;
    f = fa[x];
    lf = done[lc[f]] ? lc[f] : 0;
    rt = done[rc[f]] ? rc[f] : 0;
    if (x == lf) y = rt;
    else y = lf;
    sx = cntChild.Sum( le[x], ri[x] );
    sy = cntChild.Sum( le[y], ri[y] );
    if ( sx > sy || ( sx == sy && check(x, y, f, curt) ) ) {
      cntPath.Add( le[x], ri[x], -1 );
      cntPath.Add( le[y], ri[y], 1 );
      su = su + x - y;
    }
    x = f;
  }
}

inline bool cmp(int x, int y) {
  return dep[x] < dep[y];
}

int main(){
#ifdef ONLINE_JUDGE
  freopen("heavylight.in", "r", stdin);
  freopen("heavylight.out", "w", stdout);
#endif
  while (scanf("%d", &n), n) {
    Seg :: Min[0] = 1e9;
    Seg :: Max[0] = 0;
    Seg :: Sz = su = m = clo = 0;
    cntPath.Init();
    cntChild.Init();
    memset( vis, 0, sizeof (bool) * (n + 1) );
    memset( done, 0, sizeof (bool) * (n + 1) );
    for (int i = 1; i <= n; i ++)
      scanf("%d%d", &lc[i], &rc[i]);
    Dfs(1, 0);
    scanf("%d", &q);
    for (int i = 1; i <= q; i ++)
      scanf("%d", &a[i]), vis[a[i]] = 1, tim[a[i]] = i;
    for (int i = 1; i <= n; i ++)
      if (!vis[i]) id[++ m] = i, tim[i] = q + 1;
    sort(id + 1, id + m + 1, cmp);
    Build(1);
    for (int i = 1; i <= m; i ++) AddLeaf(id[i]);
    ans[q + 1] = su;
    for (int i = q; i >= 1; i --) AddLeaf(a[i]), ans[i] = su;
    for (int i = 1; i <= q + 1; i ++) printf("%lld\n", ans[i]);
  }
  return 0;
}
