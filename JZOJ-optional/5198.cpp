#include <bits/stdc++.h>
using namespace std;

typedef pair <int, int> pii;
const int N = 2e5 + 50;

pii b[N];

namespace Treap {
  int lc[N], rc[N], sz[N], rnd[N];
  inline void Init() {
    srand(20011227);
    for (int i = 1; i < N; i ++) {
      rnd[i] = rand(); sz[i] = 1;
    }
  }
  inline void up(int x) {
    sz[x] = sz[lc[x]] + sz[rc[x]] + 1;
  }
  inline pii split(int x, int v) {
    if (v > sz[x]) return pii(x, 0);
    if (!v) return pii(0, x);
    if (v <= sz[lc[x]]) {
      pii p = split(lc[x], v);
      lc[x] = p.second;
      up(x); return pii(p.first, x);
    } else {
      pii p = split(rc[x], v - sz[lc[x]] - 1);
      rc[x] = p.first;
      up(x); return pii(x, p.second);
    }
  }
  inline int merge(int x, int y) {
    if (!x || !y) return x + y;
    if (rnd[x] > rnd[y]) {
      rc[x] = merge(rc[x], y);
      up(x); return x;
    } else {
      lc[y] = merge(x, lc[y]);
      up(y); return y;
    }
  }
  inline void Dfs(int x) {
    if (lc[x]) Dfs(lc[x]);
    printf("%d\n", b[x].first);
    if (rc[x]) Dfs(rc[x]);
  }
}

namespace Bit {
#define lb(x) (x & (- (x)))
  int a[N];
  inline void Add(int x) {
    for (; x < N; x += lb(x)) a[x] ++;
  }
  inline int Sum(int x) {
    int res = 0;
    for (; x > 0; x -= lb(x)) res += a[x];
    return res;
  }
}

int tab[N], a[N], rnk[N], n, k;

int main() {
  freopen("fable.in", "r", stdin);
  freopen("fable.out", "w", stdout);
  scanf("%d%d", &n, &k);
  for (int i = 1; i <= n; i ++) {
    scanf("%d", &a[i]); tab[i] = a[i]; b[i] = pii(a[i], i);
  }
  sort(tab + 1, tab + n + 1);
  sort(b + 1, b + n + 1, greater <pii> ());
  for (int i = 1, p; i <= n; i ++) {
    p = lower_bound(tab + 1, tab + n + 1, a[i]) - tab;
    Bit :: Add(p);
    rnk[i] = max(0, (i - Bit :: Sum(p)) - k);
  }
  int rt = 0;
  Treap :: Init();
  for (int i = 1, x; i <= n; i ++) {
    x = b[i].second;
    pii p = Treap :: split(rt, rnk[x]);
    rt = Treap :: merge(Treap :: merge(p.first, i), p.second);
  }
  Treap :: Dfs(rt);
  return 0;
}
