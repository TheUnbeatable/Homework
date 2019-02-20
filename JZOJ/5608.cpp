#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
const int N = 1e5 + 50;

struct Bit {
#define lb(x) (x & (- x))
  int a[N];
  int vis[N], cur;
  Bit() {
    cur = 1; memset(vis, 0, sizeof vis);
  }
  inline void Init() { cur ++; }
  inline void Add(int p, int v) {
    for (; p < N; p += lb(p)) {
      if (vis[p] == cur) a[p] += v;
      else vis[p] = cur, a[p] = v;
    }
  }
  inline int Sum(int p) {
    int res = 0;
    for (; p > 0; p -= lb(p))
      if (vis[p] == cur) res += a[p];
    return res;
  }
} bit;

int a[N], b[N], c[N], n;
pair <int, int> o[N];
int bef[N];

inline void Divide(int L, int R) {
  if (L == R) {
    o[L] = make_pair(b[L], L);
    return;
  }
  int mid = (L + R) >> 1;
  Divide(L, mid);
  Divide(mid + 1, R);
  bit.Init();
  inplace_merge(o + L, o + mid + 1, o + R + 1);
  for (int i = L; i <= R; i ++) {
    if (o[i].second <= mid) bit.Add(c[o[i].second], 1);
    else bef[o[i].second] += bit.Sum(c[o[i].second]);
  }
}

inline LL calc(int *p, int *q) {
  for (int i = 1; i <= n; i ++)
    o[i] = make_pair(p[i], q[i]);
  sort(o + 1, o + n + 1);
  LL res = 0; bit.Init();
  for (int i = 1, t; i <= n; i ++) {
    t = bit.Sum(o[i].second);
    bit.Add(o[i].second, 1);
    res += (LL) t * (t - 1) / 2;
  }
  return res;
}

int main() {
  freopen("subset.in", "r", stdin);
  freopen("subset.out", "w", stdout);
  scanf("%d", &n);
  for (int i = 1; i <= n; i ++) scanf("%d", &a[i]);
  for (int i = 1; i <= n; i ++) scanf("%d", &b[a[i]]);
  for (int i = 1; i <= n; i ++) scanf("%d", &c[a[i]]), a[i] = i;
  Divide(1, n);
  LL ans = n + (LL) n * (n - 1) / 2 + (LL) n * (n - 1) * (n - 2) / 6;
  LL X = calc(a, b) + calc(a, c) + calc(b, c), A = 0;
  for (int i = 1; i <= n; i ++)
    ans -= bef[i], A += (LL) bef[i] * (bef[i] - 1) / 2;
  printf("%lld\n", ans - (X - 2 * A));
  return 0;
}
