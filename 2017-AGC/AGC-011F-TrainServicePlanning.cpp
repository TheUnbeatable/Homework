#include <cstdio>
#include <iostream>
#define mid ((L + R) >> 1)
using namespace std;

typedef long long LL;
const int N = 1e5 + 50;

int n, K;
LL a[N], L[N], R[N], dp[N];
int rt = 1, Sz = 1, B[N];
int lc[N << 6], rc[N << 6], tag[N << 6];

inline void Modify(int l, int r, int v, int &x = rt, int L = 0, int R = K - 1) {
  if (!x) {
    x = ++ Sz; tag[x] = 1e9;
  }
  if (l <= L && R <= r) return (void) (tag[x] = v);
  if (l <= mid) Modify(l, r, v, lc[x], L, mid);
  if (r > mid) Modify(l, r, v, rc[x], mid + 1, R);
}

inline int Query(int p, int x = rt, int L = 0, int R = K - 1) {
  if (!x) return (int)1e9;
  if (p <= mid) return min(tag[x], Query(p, lc[x], L, mid));
  if (p > mid) return min(tag[x], Query(p, rc[x], mid + 1, R));
}

template <typename T> inline void chkmin(T &x, T y) { if (x > y) x = y; }

int main() {
  tag[1] = 1e9;
  scanf("%d%d", &n, &K);
  for (int i = 1, x; i <= n; i ++) {
    scanf("%d%d", &x, &B[i]);
    a[i] = a[i - 1] + x;
    L[i] = - (a[i] << 1) + 1;
    R[i] = - (a[i - 1] << 1) - 1;
    if ((x << 1) > K && B[i] == 1) return 0 * puts("-1");
  }
  for (int i = n, l, r, nxt; i >= 1; i --) {
    l = L[i] % K; if (l < 0) l += K;
    r = R[i] % K; if (r < 0) r += K;
    nxt = Query((r + 1) % K);
    if (B[i] == 1) {
      if (l <= r) Modify(l, r, i);
      else {
        Modify(0, r, i);
        Modify(l, K - 1, i);
      }
    }
    if (nxt != 1e9) dp[i] = dp[nxt] + ((R[nxt] + 1 - (R[i] + 1)) % K + K) % K;
  }
  LL ans = 1e18;
  for (int i = 1, nxt; i <= n; i ++) {
    nxt = Query((L[i] % K - 1 + K + K) % K);
    if (nxt != 1e9) chkmin(ans, dp[nxt] + ((R[nxt] + 1 - (L[i] - 1)) % K + K) % K);
    else ans = 0;
    nxt = Query((R[i] % K + 1 + K) % K);
    if (nxt != 1e9) chkmin(ans, dp[nxt] + ((R[nxt] + 1 - (R[i] + 1)) % K + K) % K);
    else ans = 0;
  }
  printf("%lld\n", ans + a[n] + a[n]);
  return 0;
}
