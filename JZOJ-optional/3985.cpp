#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
const int N = 1e5 + 50;

#define mid ((L + R) >> 1)

int n, a[N];
LL sum[N << 2];
int Max[N << 2];
set <int> pos[N];
int lst[N];

inline LL Calc(int v, int x, int L, int R) {
  if (v >= Max[x]) return (LL)(R - L + 1) * v;
  if (L == R) return Max[x];
  if (v >= Max[x << 1])
    return (LL)(mid - L + 1) * v + Calc(v, x << 1 | 1, mid + 1, R);
  else
    return Calc(v, x << 1, L, mid) + sum[x] - sum[x << 1];
}

inline void Modify(int p, int v, int x = 1, int L = 1, int R = n) {
  if (L == R) {
    Max[x] = sum[x] = v; return;
  }
  if (p <= mid) Modify(p, v, x << 1, L, mid);
  else Modify(p, v, x << 1 | 1, mid + 1, R);
  Max[x] = max(Max[x << 1], Max[x << 1 | 1]);
  sum[x] = sum[x << 1] + Calc(Max[x << 1], x << 1 | 1, mid + 1, R);
}

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i ++) {
    scanf("%d", &a[i]);
    Modify(i, lst[a[i]]);
    lst[a[i]] = i;
    pos[a[i]].insert(i);
  }
  int q; scanf("%d", &q);
  for (int o, p, v; q; q --) {
    scanf("%d", &o);
    if (!o) printf("%lld\n", (LL)n * (n + 1) / 2 - sum[1]);
    else {
      scanf("%d%d", &p, &v);
      set <int> :: iterator it = pos[a[p]].find(p), tmp;
      int lst = 0, nxt = 0;
      if (it != pos[a[p]].begin()) {
        tmp = it; it --; lst = *it; it = tmp;
      }
      { tmp = it; it ++;
        if (it != pos[a[p]].end()) nxt = *it;
        it = tmp; }
      if (nxt) Modify(nxt, lst);
      pos[a[p]].erase(it);

      a[p] = v;
      it = pos[v].insert(p).first;
      lst = nxt = 0;
      if (it != pos[v].begin()) {
        tmp = it; it --; lst = *it; it = tmp;
      }
      { tmp = it; it ++;
        if (it != pos[v].end()) nxt = *it;
        it = tmp; }
      Modify(p, lst);
      if (nxt) Modify(nxt, p);
    }
  }
  return 0;
}
