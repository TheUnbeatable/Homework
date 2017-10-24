#include <cstdio>
#include <iostream>
using namespace std;

typedef long long LL;
const int N = 2e5 + 5;
const LL mod = 1e9 + 7;

LL fac[N], inv[N];

inline LL pow(LL x, LL exp) {
  LL ret = 1;
  while (exp) {
    if (exp & 1) ret = ret * x % mod;
    exp >>= 1;
    x = x * x % mod;
  }
  return ret;
}

inline void pre() {
  fac[0] = inv[0] = 1;
  for (LL i = 1; i < N; i ++) fac[i] = fac[i - 1] * i % mod;
  inv[N - 1] = pow(fac[N - 1], mod - 2);
  for (LL i = N - 2; i >= 1; i --) inv[i] = inv[i + 1] * (i + 1) % mod;
}

inline LL Co(int n, int m) {
  return fac[n] * inv[m] % mod * inv[n - m] % mod;
}

int main() {
  pre();
  int n, m, a, b;
  LL ans = 0;
  scanf("%d%d%d%d", &n, &m, &a, &b);
  for (int i = b + 1; i <= m; i ++) {
    int r1 = i - 1, d1 = n - a - 1;
    int r2 = m - 1 - r1, d2 = n - 2 - d1;
    ans += Co(r1 + d1, r1) * Co(r2 + d2, r2) % mod;
    if (ans >= mod) ans -= mod;
  }
  printf("%lld\n", ans);
  return 0;
}
