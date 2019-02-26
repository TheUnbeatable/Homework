#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
const int N = 1040;
const int mod = 1e9 + 7;
const LL sqr = 5ll * mod * mod;

int n, m, c, r, p[44][12][5], f[N][36], g[N][36];

inline void calc(int x) {
  memset(g, 0, sizeof g);
  g[0][0] = 1;
  for (int i = 1; i < (1 << m); i ++) {
    for (int j = 0; j < m; j ++)
      if ((i >> j) & 1) {
        int *from = g[i ^ (1 << j)], *to = g[i];
        for (int k = 0; k <= r; k ++)
          if (from[k])
            for (int a = 0; a <= c; a ++)
              to[k + a] = (to[k + a] + 1ll * from[k] * p[x][j][a]) % mod;
        break;
      }
  }
}

inline void add() {
  static int swp[N][36];
  static LL tmp[36], pf[N][36], pg[N][36];
  for (int i = 0; i < (1 << m); i ++) {
    pf[i][0] = f[i][0];
    pg[i][0] = g[i][0];
    for (int j = 1; j <= r; j ++) {
      pg[i][j] = (g[i][j] + pg[i][j - 1]) % mod;
      pf[i][j] = (f[i][j] + pf[i][j - 1]) % mod;
    }
  }
  for (int i = 0; i < (1 << m); i ++) {
    memset(tmp, 0, sizeof tmp);
    for (int j = i; ; j = (j - 1) & i) {
      tmp[0] += pf[j][0] * pg[i ^ j][0];
      if (tmp[0] >= sqr) tmp[0] -= sqr;
      for (int k = 1; k <= r; k ++) {
        tmp[k] += f[j][k] * pg[i ^ j][k] + g[j][k] * pf[i ^ j][k - 1];
        (tmp[k] >= sqr ? tmp[k] -= sqr : 0);
      }
      if (!j) break;
    }
    for (int k = 0; k <= r; k ++) swp[i][k] = tmp[k] % mod;
  }
  memcpy(f, swp, sizeof f);
}

int main() {
  freopen("max.in", "r", stdin);
  freopen("max.out", "w", stdout);
  scanf("%d%d%d", &n, &m, &c);
  for (int i = 0; i < m; i ++)
    for (int j = 1; j <= n; j ++)
      for (int k = 0; k <= c; k ++) scanf("%d", &p[j][i][k]);
  r = c * m;
  f[0][0] = 1;
  for (int i = 1; i <= n; i ++) { calc(i); add(); }
  LL ans = 0;
  for (int i = 1; i <= r; i ++)
    ans += (LL) i * f[(1 << m) - 1][i];
  printf("%lld\n", ans % mod);
  return 0;
}
