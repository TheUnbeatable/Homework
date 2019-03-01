#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
const int M = 14, N = 1 << M | 5;
const int mod = 998244353;

int fac[N], ifac[N];

namespace Poly {
  int w[N], rev[N];
  inline LL Pow(LL x, LL exp = mod - 2) {
    LL res = 1;
    for (; exp; exp >>= 1, x = x * x % mod)
      if (exp & 1) res = res * x % mod;
    return res;
  }
  inline void Init() {
    fac[0] = w[0] = 1;
    LL per = Pow(3, (mod - 1) >> M);
    for (int i = 1; i < N; i ++) {
      if (i & 1) rev[i] = rev[i - 1] | (1 << (M - 1));
      else rev[i] = rev[i >> 1] >> 1;
      w[i] = w[i - 1] * per % mod;
      fac[i] = (LL) fac[i - 1] * i % mod;
    }
    ifac[N - 1] = Pow(fac[N - 1]);
    for (int i = N - 1; i; i --)
      ifac[i - 1] = (LL) ifac[i] * i % mod;
  }
  inline void Dft(int *a) {
    int E = 1 << M;
    for (int i = 1; i < E; i ++)
      if (rev[i] < i) swap(a[rev[i]], a[i]);
    register int y;
    static int swp[N];
    for (int i = 1, d = 1; i <= M; i ++, d <<= 1) {
      for (int j = 0, k = 0; k < d; j += (E >> i), k ++) swp[k] = w[j];
      for (int j = 0; j < E; j += d + d)
        for (int k = j; k < j + d; k ++) {
          y = (LL) a[k + d] * swp[k - j] % mod;
          a[k + d] = (a[k] >= y ? a[k] - y : a[k] - y + mod);
          (a[k] += y) >= mod ? a[k] -= mod : 0;
        }
    }
  }
  inline void IDft(int *a) {
    int E = 1 << M;
    reverse(a + 1, a + E); Dft(a);
    LL inv = Pow(E);
    for (int i = 0; i < E; i ++) a[i] = a[i] * inv % mod;
  }
}
using Poly :: Dft;
using Poly :: IDft;

int a[N], b[N], s[N], r[N];
int n, m;

inline LL C(int x, int y) {
  return (LL) fac[x] * ifac[y] % mod * ifac[x - y] % mod;
}

int main() {
  Poly :: Init();
  scanf("%d%d", &n, &m);
  int *x = a, *y = b;
  for (int i = 0; i <= n; i ++) r[i] = ifac[i + 2];
  Dft(r);
  x[0] = 1;
  for (int t = 1; t <= m; t ++) {
    memset(y, 0, sizeof a);
    for (int i = 1; i <= n; i ++) {
      y[i] = (mod - x[i] * C(i + 2, 2) % mod
              + x[i] * ( C(i + 1, 2) + 1 ) ) % mod;
      x[i] = (LL) x[i] * ifac[i] % mod;
    }
    Dft(x);
    for (int i = 0; i < N; i ++)
      x[i] = (LL) x[i] * r[i] % mod;
    IDft(x);
    y[0] = 1;
    for (int i = 1; i <= n; i ++)
      y[i] = ( y[i] + (LL) x[i] * fac[i + 2] ) % mod;
    swap(x, y);
  }
  LL ans = 0;
  for (int i = 0; i <= n; i ++) ans += C(n, i) * x[i] % mod;
  printf("%lld\n", (ans % mod + mod) % mod);
  return 0;
}
