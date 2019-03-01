#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
const int N = 1e6 + 50;
const int mod = 998244353;

namespace MathCal {
  LL fac[N], inv[N];

  inline LL Pow(LL x, LL exp) {
    LL res = 1;
    for (; exp; exp >>= 1, x = x * x % mod)
      if (exp & 1) res = res * x % mod;
    return res;
  }
  inline void Init() {
    for (int i = fac[0] = 1; i < N; i ++) fac[i] = fac[i - 1] * i % mod;
    inv[N - 1] = Pow(fac[N - 1], mod - 2);
    for (int i = N - 1; i; i --) inv[i - 1] = inv[i] * i % mod;
  }
  inline LL C(int x, int y) {
    return y > x ? 0 : fac[x] * inv[y] % mod * inv[x - y] % mod;
  }
}
using MathCal :: C;

int n, k;

inline LL calc(int x, int y, int k) {
  k ++;
  return C(x + y, x) - C(x + y, x + k);
}

int main() {
  MathCal :: Init();
  scanf("%d%d", &n, &k);
  LL ans = 0;
  for (int A = n, B; A <= k; A ++) {
    B = k - A;
    if (A < B) continue;
    if (A == B) ans += calc(A, A - 1, A - n);
    else ans += calc(A, B, A - n);
  }
  printf("%lld\n", (ans % mod + mod) % mod);
  return 0;
}
