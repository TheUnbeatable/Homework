#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 2e5 + 50;

struct edge {
  int nxt, to;
} e[N << 1];
int fir[N], cnt = 1;
int a[N], b[N], n, m;
double mid, res, fix[N];
double *totop[N];
int idlist[N], tot, id[N], pref[N];
int dep[N], top[N], Max[N], fa[N], siz[N];

template <typename T1, typename T2>
inline void chkmin(T1 &p, T2 q) { if (p > q) p = q; }

inline void addedge(int x, int y) {
  e[++ cnt] = (edge) { fir[x], y }; fir[x] = cnt;
}

inline void Dfs(int x, int f) {
  // calculate the maximum depth for all subtrees
  fa[x] = f;
  Max[x] = dep[x] = dep[f] + 1;
  for (int i = fir[x]; i; i = e[i].nxt)
    if (e[i].to != f) {
      Dfs(e[i].to, x);
      Max[x] = max(Max[x], Max[e[i].to]);
    }
}

inline void Build(int x, int f) {
  // division by depth
  bool chosen = 0;
  if (top[x] == x) {
    siz[x] = Max[x] - dep[x];
    totop[x] = new double[siz[x] + 1];
    idlist[++ tot] = x;
  }
  for (int i = fir[x]; i; i = e[i].nxt)
    if (e[i].to != f) {
      if (!chosen && Max[e[i].to] == Max[x]) {
        chosen = 1;
        pref[x] = e[i].to;
        top[e[i].to] = top[x];
      }
      else top[e[i].to] = e[i].to;
      Build(e[i].to, x);
    }
}

inline bool cmp(int p, int q) { return dep[p] < dep[q]; }

inline double DP(int x, int f) {
  // find the smallest-weight path
  if (res < 0) return 0;
  double ret = a[x] - b[x] * mid, k;
  for (int i = fir[x]; i; i = e[i].nxt)
    if (e[i].to != f) {
      k = DP(e[i].to, x);
      chkmin(res, ret + k);
      chkmin(ret, k);
    }
  return ret;
}

int sta[N];

inline void insertTop(int x) {
  if (res < 0) return;
  // update the contribution to the top of a segment
  int tp = top[x];
  double *des = totop[tp];
  int xtop = dep[x] - dep[tp];
  int dtop = dep[x] - dep[tp] + 1;
  double wei = fix[x] - fix[fa[tp]];
  double sub = fix[fa[x]] - fix[fa[tp]];
  chkmin(des[xtop], wei);
  if (xtop + m <= siz[tp])
    chkmin(res, des[xtop + m] - sub);
  for (int w = fir[x]; w; w = e[w].nxt)
    if (e[w].to != fa[x] && e[w].to != pref[x]) {
      int y = e[w].to;
      double *fro = totop[y];
      for (int i = 0; i <= siz[y]; i ++)
        if (xtop + m - i - 1 <= siz[tp] && xtop + m - i - 1 >= 0)
          chkmin(res, fro[i] + des[xtop + m - i - 1] - sub);
      for (int i = 0; i <= siz[y]; i ++)
        chkmin(des[dtop + i], fro[i] + wei);
    }
}

inline void update(int x) {
  if (res < 0) return;
  int ptr = 0;
  for (int i = x; i; i = pref[i]) sta[++ ptr] = i;
  for (int i = ptr; i; i --) insertTop(sta[i]);
}

inline void check() {
  res = 1;
  if (m == -2) return (void) DP(1, 0);
  for (int i = 1; i <= n; i ++) {
    if (top[i] != i) continue;
    memset(totop[i], 127, sizeof(double) * (siz[i] + 1));
  }
  for (int i = 1, j; i <= n; i ++) {
    j = id[i];
    fix[j] = fix[fa[j]] + a[j] - b[j] * mid;
  }
  for (int i = tot; i; i --) update(idlist[i]);
}

int main() {
  freopen("cdcq_b.in", "r", stdin);
  freopen("cdcq_b.out", "w", stdout);
  scanf("%d%d", &n, &m); m --;
  for (int i = 1; i <= n; i ++) scanf("%d", &a[i]);
  for (int i = 1; i <= n; i ++) scanf("%d", &b[i]);
  for (int i = 1, x, y; i < n; i ++) {
    scanf("%d%d", &x, &y);
    addedge(x, y); addedge(y, x);
  }
  if (m != -2) {
    Dfs(1, 0); top[1] = 1; Build(1, 0);
    sort(idlist + 1, idlist + tot + 1, cmp);
    for (int i = 1; i <= n; i ++) id[i] = i;
    sort(id + 1, id + n + 1, cmp);
  }
  double L = 0, R = N, ans = -1;
  mid = 1; check();
  if (res <= 0) ans = mid, R = mid;
  else L = mid;
  while (R - L > 1e-5) {
    mid = (L + R) / 2;
    check();
    if (res <= 0) ans = mid, R = mid;
    else L = mid;
  }
  if (ans == -1) puts("-1");
  else printf("%.2lf\n", ans);
  return 0;
}
