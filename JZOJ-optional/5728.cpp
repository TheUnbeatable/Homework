#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
const int N = 53, M = 5050;
const int mod = 1e9 + 7;
const LL sqr = 4ll * mod * mod;

int C[110][110], fac[M], ifac[M];
int f[N][M], g[110][110], h[110], p[N], n;

inline LL Pow(LL x, LL exp = mod - 2) {
  LL res = 1;
  for (; exp; exp >>= 1, x = x * x % mod)
    if (exp & 1) res = res * x % mod;
  return res;
}

int main() {
  freopen("number.in", "r", stdin);
  freopen("number.out", "w", stdout);
  scanf("%d", &n);
  for (int i = 1; i <= n; i ++) scanf("%d", &p[i]);
  if (n == 1) {
    printf("%d\n", p[1]);
    return 0;
  }
  for (int i = 0; i <= 100; i ++) {
    C[i][0] = 1;
    for (int j = 1; j <= i; j ++) {
      C[i][j] = C[i - 1][j - 1] + C[i - 1][j];
      if (C[i][j] >= mod) C[i][j] -= mod;
    }
  }
  for (int i = ifac[0] = fac[0] = 1; i < M; i ++) {
    fac[i] = (LL)i * fac[i - 1] % mod;
    ifac[i] = Pow(fac[i]);
  }
  g[0][0] = 1;
  for (int i = 1; i <= 100; i ++)
    for (int j = 1; j <= i; j ++) {
      LL res = 0;
      for (int k = 1; k <= i; k ++)
        res += (LL)g[i - k][j - 1] * k;
      g[i][j] = res % mod;
    }
  int csum = 0;
  f[0][0] = 1;
  for (int i = 1; i <= n; i ++) {
    int q = p[i];
    for (int b = 1; b <= q; b ++) {
      LL res = 0;
      for (int a = b, s = 1; a <= q; a ++, s = -s) {
        if (i != n)
          (res += (LL)s * C[a - 1][b - 1] * ifac[b] % mod * g[q][a]) %= mod;
        else
          (res += (LL)s * C[a - 1][b - 1] * ifac[b - 1] % mod * g[q][a] % mod * Pow(a)) %= mod;
      }
      h[b] = (res + mod) % mod;
    }
    csum += q;
    for (int j = i; j <= csum; j ++) {
      LL res = 0;
      for (int b = 1; b <= q && b <= j; b ++) {
        res += (LL)f[i - 1][j - b] * h[b];
        if (res >= sqr) res -= sqr;
      }
      f[i][j] = res % mod;
      if (i == n - 1) f[i][j] = (LL)f[i][j] * j % mod;
    }
  }
  LL ans = 0;
  for (int i = n; i <= csum; i ++)
    (ans += (LL)f[n][i] * fac[i - 2]) %= mod;
  printf("%lld\n", ans * csum % mod);
  return 0;
}
