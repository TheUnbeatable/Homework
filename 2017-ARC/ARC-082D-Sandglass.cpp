#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#define lc (x << 1)
#define rc (x << 1 | 1)
using namespace std;

const int N = 1e5 + 10;
const int inf = 2e9;

int mx[N << 2], mn[N << 2], lazy_to[N << 2], lazy_add[N << 2];
int id[N];
int t[N], a[N], r[N], ans[N], tab[N];
int X, q, k;

inline void pushup(int x) {
  mx[x] = max(mx[lc], mx[rc]);
  mn[x] = min(mn[lc], mn[rc]);
}

inline void pushdown(int x) {
  if (lazy_to[x] == inf) {
    if (!lazy_add[x]) return;
    if (lazy_to[lc] == inf) lazy_add[lc] += lazy_add[x];
    else lazy_to[lc] += lazy_add[x];
    if (lazy_to[rc] == inf) lazy_add[rc] += lazy_add[x];
    else lazy_to[rc] += lazy_add[x];
    mx[lc] += lazy_add[x];
    mn[lc] += lazy_add[x];
    mx[rc] += lazy_add[x];
    mn[rc] += lazy_add[x];
  }
  else {
    lazy_to[lc] = lazy_to[rc] = mx[lc] = mx[rc] = mn[lc] = mn[rc] = lazy_to[x];
    lazy_add[lc] = lazy_add[rc] = 0;
  }
  lazy_to[x] = inf;
  lazy_add[x] = 0;
}

inline void build(int x, int l, int r) {
  lazy_to[x] = inf;
  if (l == r) {
    mx[x] = mn[x] = tab[l];
    return;
  }
  int mid = (l + r) >> 1;
  build(lc, l, mid);
  build(rc, mid + 1, r);
  pushup(x);
}

inline void adjust_to_zero(int x, int l, int r) {
  if (mx[x] <= 0) {
    lazy_to[x] = lazy_add[x] = mx[x] = mn[x] = 0;
    return;
  }
  pushdown(x);
  int mid = (l + r) >> 1;
  if (mn[lc] < 0) adjust_to_zero(lc, l, mid);
  if (mn[rc] < 0) adjust_to_zero(rc, mid + 1, r);
  pushup(x);
}

inline void adjust_to_x(int x, int l, int r) {
  if (mn[x] >= X) {
    lazy_to[x] = mx[x] = mn[x] = X;
    lazy_add[x] = 0;
    return;
  }
  pushdown(x);
  int mid = (l + r) >> 1;
  if (mx[lc] > X) adjust_to_x(lc, l, mid);
  if (mx[rc] > X) adjust_to_x(rc, mid + 1, r);
  pushup(x);
}

inline int query(int x, int l, int r, int pos) {
  if (l == r) return mx[x];
  pushdown(x);
  int mid = (l + r) >> 1, ret;
  if (pos <= mid) ret = query(lc, l, mid, pos);
  else ret = query(rc, mid + 1, r, pos);
  pushup(x);
  return ret;
}

inline bool cmp(int a, int b) {
  return t[a] < t[b];
}

int main() {
  scanf("%d%d", &X, &k);
  for (int i = 1; i <= k; i ++) scanf("%d", &r[i]);
  scanf("%d", &q);
  for (int i = 1; i <= q; id[i] = i, i ++) {
    scanf("%d%d", &t[i], &a[i]);
    tab[i] = a[i];
  }
  sort(id + 1, id + q + 1, cmp);
  sort(tab + 1, tab + q + 1);
  if (t[id[q]] > r[k]) r[++ k] = t[id[q]] + 1;
  build(1, 1, q);
  int pos = 1, tmp, ppp;
  for (int i = 1; i <= k && pos <= q; i ++) {
    while (t[id[pos]] <= r[i] && pos <= q) {
      ppp = lower_bound(tab + 1, tab + q + 1, a[id[pos]]) - tab;
      tmp = query(1, 1, q, ppp);
      if (i & 1) ans[id[pos]] = max(tmp - (t[id[pos]] - r[i - 1]), 0);
      else ans[id[pos]] = min(tmp + (t[id[pos]] - r[i - 1]), X);
      pos ++;
    }
    int ttt = r[i] - r[i - 1];
    if (i & 1) {
      mx[1] -= ttt;
      mn[1] -= ttt;
      if (lazy_to[1] == inf) lazy_add[1] -= ttt;
      else lazy_to[1] -= ttt, lazy_add[1] = 0;
      adjust_to_zero(1, 1, q);
    }
    else {
      mx[1] += ttt;
      mn[1] += ttt;
      if (lazy_to[1] == inf) lazy_add[1] += ttt;
      else lazy_to[1] += ttt, lazy_add[1] = 0;
      adjust_to_x(1, 1, q);
    }
  }
  for (int i = 1; i <= q; i ++) printf("%d\n", ans[i]);
  return 0;
}
