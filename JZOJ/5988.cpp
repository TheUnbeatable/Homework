#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
const int N = 2e6 + 70;
const LL mod = 998244353;

LL fac[N], inv[N];

inline LL Pow(LL x, LL exp = mod - 2) {
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

int main() {
  freopen("tree.in", "r", stdin);
  freopen("tree.out", "w", stdout);
  int n;
  Init();
  scanf("%d", &n);
  LL ans = 0;
  for (int i = 2, d; i <= n + n; i += 2) {
    d = __gcd(i, n * 2);
    ans += C(d, d / 2);
  }
  ans %= mod;
  printf("%lld\n", ans * Pow(n * 2) % mod);
  return 0;
}
