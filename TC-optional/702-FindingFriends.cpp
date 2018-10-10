#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;

const int N = 1e5 + 50;

int a[N], n, id[N], tab[N], m;

inline bool cmp(int p, int q) { return a[p] < a[q]; }

namespace Tree {
#define mid ((L + R) >> 1)
  const int M = N * 23;
  int rt[N], lc[M], rc[M], sum[M], Sz = 0;

  inline void Add(int &x, int y, int p, int L = 1, int R = n) {
    x = ++ Sz;
    sum[x] = sum[y] + 1;
    if (L == R) return;
    if (p <= mid) {
      Add(lc[x], lc[y], p, L, mid);
      rc[x] = rc[y];
    } else {
      lc[x] = lc[y];
      Add(rc[x], rc[y], p, mid + 1, R);
    }
  }
  inline int RightMost(int rb, int x, int y, int L = 1, int R = n) {
    if (rb < 1 || rb > n) return -1;
    if (sum[y] - sum[x] == 0) return -1;
    if (L == R) return L;
    if (rb <= mid) return RightMost(rb, lc[x], lc[y], L, mid);
    int t = RightMost(rb, rc[x], rc[y], mid + 1, R);
    if (t != -1) return t;
    return RightMost(rb, lc[x], lc[y], L, mid);
  }
  inline int LeftMost(int lb, int x, int y, int L = 1, int R = n) {
    if (lb < 1 || lb > n) return n + 1;
    if (sum[y] - sum[x] == 0) return n + 1;
    if (L == R) return L;
    if (lb > mid) return LeftMost(lb, rc[x], rc[y], mid + 1, R);
    int t = LeftMost(lb, lc[x], lc[y], L, mid);
    if (t != n + 1) return t;
    return LeftMost(lb, rc[x], rc[y], mid + 1, R);
  }
  inline void Init() {
    for (int i = 1; i <= n; i ++) id[i] = i;
    sort(id + 1, id + n + 1, cmp);
    for (int i = 1; i <= n; i ++) tab[i] = a[id[i]];
    for (int i = 1; i <= n; i ++)
      Add(rt[i], rt[i - 1], id[i]);
  }
#undef mid
}
using Tree :: rt;
using Tree :: LeftMost;
using Tree :: RightMost;

int le[N], ri[N];

inline bool Dfs(int l, int r) {
  if (r - l + 1 < m) return 0;
  int divi = 0;
  for (register int i = 0; ; i ++) {
    if (l + i > r - i) break;
    if (le[l + i] < l && ri[l + i] > r) {
      divi = l + i; break;
    }
    if (le[r - i] < l && ri[r - i] > r) {
      divi = r - i; break;
    }
  }
  if (!divi) return 1;
  if (Dfs(l, divi - 1)) return 1;
  return Dfs(divi + 1, r);
}

inline int find(int x) {
  if (x < tab[1]) return 0;
  if (x > tab[n]) return n + 1;
  return lower_bound(tab + 1, tab + n + 1, x) - tab;
}

int lp[N], lq[N];

inline bool check(int x) {
  for (int i = 1, p, q; i <= n; i ++) {
    p = find(a[i] - x) - 1;
    q = find(a[i] + x + 1) - 1;
    if (p == lp[i] && q == lq[i]) continue;
    lp[i] = p; lq[i] = q;
    le[i] = RightMost(i - 1, rt[p], rt[q]);
    ri[i] = LeftMost(i + 1, rt[p], rt[q]);
  }
  return Dfs(1, n);
}

class FindingFriends {
public:
  inline int shortestDistance(int len, vector <int> init,
                              int _a, int b, int c, int d, int _m) {
    for (int i = 0; i < (int)init.size(); i ++)
      a[i + 1] = init[i];
    :: n = len;
    :: m = _m;
    for (int i = init.size() + 1; i <= len; i ++)
      a[i] = ( 1ll * a[i - 1] * _a + 1ll * b * (i - 1) + c ) % d;
    Tree :: Init();
    int L = 0, R = 1e9, mid, ans = -1;
    if (check(100000)) ans = 100000, R = ans - 1;
    while (L <= R) {
      mid = (L + R) >> 1;
      if (check(mid)) ans = mid, R = mid - 1;
      else L = mid + 1;
    }
    return ans;
  }
};

int main() {
  FindingFriends solver;
  cerr << solver.shortestDistance(100000, {967948965}, 758179342, 788391896, 28648718, 999999937, 3) << endl;
  return 0;
}
