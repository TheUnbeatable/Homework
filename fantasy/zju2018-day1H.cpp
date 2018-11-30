#include <cstdio>
#include <iostream>
#include <cstring>
using namespace std;

typedef long long LL;
const int N = 40;
const int M = 20;

LL G[N];
int n, m, k, a[N], nim[N];
int cnt[16][1 << M | 5], sum[1 << M | 5];
int dp[40100];
int vis[300], cur;

inline int calc(int x) {
  dp[0] = 0;
  for (int i = 1; i <= a[x]; i ++) {
    cur ++;
    for (int j = 0; j < n; j ++)
      if ((G[x] >> j) & 1) {
        if (i <= a[j]) vis[0] = cur;
        else vis[dp[i - a[j]]] = cur;
      }
    for (int j = 0; ; j ++)
      if (vis[j] != cur) {
        dp[i] = j; break;
      }
  }
  return dp[a[x]];
}

inline void FMT(int *a) {
  for (int i = 0; i < k; i ++)
    for (int j = 0; j < (1 << k); j += (2 << i))
      for (int l = j; l < j + (1 << i); l ++)
        a[l + (1 << i)] += a[l];
}

inline void solve() {
  scanf("%d", &n);
  for (int i = 0; i < n; i ++) scanf("%d", &a[i]);
  int cost = 2e9;
  for (int i = 1; i <= n / 2; i ++)
    if (cost > i * (1 << i) + (1ll << (n - i))) {
      cost = i * (1 << i) + (1 << (n - i)); k = i;
    }
  memset(G, 0, sizeof G);
  for (int i = 0; i < 16; i ++)
    memset(cnt[i], 0, sizeof (int) * (1 << k));
  memset(sum, 0, sizeof (int) * (1 << k));
  scanf("%d", &m);
  for (int i = 1, x, y; i <= m; i ++) {
    scanf("%d%d", &x, &y);
    x --; y --;
    if (x == y) continue;
    G[x] |= 1LL << y;
    G[y] |= 1LL << x;
  }
  for (int i = 0; i < n; i ++) nim[i] = calc(i);
  int rng = 0;
  for (int i = 0; i < (1 << k); i ++) {
    int ok = 1;
    for (int j = 0; j < k && ok; j ++)
      if ( ((i >> j) & 1) && (G[j] & i) ) ok = 0;
    if (!ok) continue;
    ok = 0;
    for (int j = 0; j < k; j ++)
      if ((i >> j) & 1) ok ^= nim[j];
    cnt[ok][i] = 1;
    rng = max(rng, ok);
  }
  for (int i = 0; i <= rng; i ++) {
    FMT(cnt[i]);
    for (int j = 0; j < (1 << k); j ++) sum[j] += cnt[i][j];
  }
  int l = n - k, U = (1 << k) - 1;
  LL fir = 0, sec = 0;
  for (int i = 0; i < (1 << l); i ++) {
    int ok = 1;
    for (int j = 0; j < l && ok; j ++)
      if ( ((i >> j) & 1) && ((G[j + k] >> k) & i) ) ok = 0;
    if (!ok) continue;
    LL state = 0;
    ok = 0;
    for (int j = 0; j < l; j ++)
      if ((i >> j) & 1) {
        state |= G[j + k] & U; ok ^= nim[j + k];
      }
    state ^= U;
    fir += sum[state] - cnt[ok][state];
    sec += cnt[ok][state];
  }
  printf("%lld\n%lld\n", fir, sec);
}

int main() {
  int T;
  scanf("%d", &T);
  while (T --) solve();
  return 0;
}
