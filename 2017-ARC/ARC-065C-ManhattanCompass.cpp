#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

typedef long long LL;
const int N = 1e5 + 10;

int n, a, b, D;
int x[N], y[N], id[N], deg[N];
int cov[N], fa[N];

inline int mabs(int x) {return x >= 0 ? x : - x;}

inline int getf(int x) {
  return fa[x] == x ? x : fa[x] = getf(fa[x]);
}

inline bool cmp(int a, int b) {
  if (x[a] != x[b]) return x[a] < x[b];
  return y[a] < y[b];
}

inline void BuildGraph1() {
  sort(id + 1, id + n + 1, cmp);
  for (int i = 1, l = 1, r = 1; i <= n; i ++) {
    if (x[id[l]] != x[id[i]] - D) {
      while (l <= n && x[id[l]] < x[id[i]] - D) l ++;
      if (x[id[l]] != x[id[i]] - D) continue;
    }
    while (l <= n && x[id[l]] == x[id[i]] - D && y[id[l]] < y[id[i]] - D) l ++;
    if (r < l) r = l;
    while (r <= n && x[id[r]] == x[id[i]] - D && y[id[r]] <= y[id[i]] + D) r ++;
    if (l < r) {
      cov[l] ++;
      cov[r - 1] --;
      fa[getf(id[i])] = getf(id[l]);
      deg[id[i]] += r - l;
    }
  }
  for (int i = 1; i <= n; i ++) {
    cov[i] += cov[i - 1];
    if (cov[i]) fa[getf(id[i])] = getf(id[i + 1]);
  }
}

inline void BuildGraph2() {
  memset(cov, 0, sizeof cov);
  sort(id + 1, id + n + 1, cmp);
  for (int i = 1, l = 1, r = 1; i <= n; i ++) {
    if (x[id[l]] != x[id[i]] - D) {
      while (l <= n && x[id[l]] < x[id[i]] - D) l ++;
      if (x[id[l]] != x[id[i]] - D) continue;
    }
    while (l <= n && x[id[l]] == x[id[i]] - D && y[id[l]] <= y[id[i]] - D) l ++;
    if (r < l) r = l;
    while (r <= n && x[id[r]] == x[id[i]] - D && y[id[r]] < y[id[i]] + D) r ++;
    if (l < r) {
      cov[l] ++;
      cov[r - 1] --;
      fa[getf(id[i])] = getf(id[l]);
      deg[id[i]] += r - l;
    }
  }
  for (int i = 1; i <= n; i ++) {
    cov[i] += cov[i - 1];
    if (cov[i]) fa[getf(id[i])] = getf(id[i + 1]);
  }
}

int main() {
  scanf("%d%d%d", &n, &a, &b);
  for (int i = 1, X, Y; i <= n; i ++) {
    scanf("%d%d", &X, &Y);
    x[i] = X + Y;
    y[i] = Y - X;
    id[i] = i;
    fa[i] = i;
  }
  D = max(mabs(x[a] - x[b]), mabs(y[a] - y[b]));
  BuildGraph1();
  for (int i = 1; i <= n; i ++) {
    id[i] = i;
    swap(x[i], y[i]);
  }
  BuildGraph2();
  int F = getf(a);
  LL ans = 0;
  for (int i = 1; i <= n; i ++)
    if (getf(i) == F) ans += deg[i];
  printf("%lld\n", ans);
  return 0;
}
