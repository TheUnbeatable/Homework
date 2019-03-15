#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
const int N = 2e5 + 50;
const int mod = 998244353;

int fac[N], ifac[N], inv[N];

inline LL Pow(LL x, LL exp) {
  LL res = 1;
  for (; exp; exp >>= 1, x = x * x % mod)
    if (exp & 1) res = res * x % mod;
  return res;
}

inline void Init() {
  for (int i = fac[0] = 1; i < N; i ++)
    fac[i] = (LL)fac[i - 1] * i % mod;
  ifac[N - 1] = Pow(fac[N - 1], mod - 2);
  for (int i = N - 1; i; i --)
    ifac[i - 1] = (LL)ifac[i] * i % mod;
  for (int i = 1; i < N; i ++)
    inv[i] = (LL)fac[i - 1] * ifac[i] % mod;
}

int f[N], n, k, T;

inline void solve() {
  scanf("%d%d", &n, &k);
  f[0] = 1;
  for (int i = 1; i <= n; i ++) {
    f[i] = f[i - 1] - (i - k - 1 >= 0 ? f[i - k - 1] : 0);
    if (f[i] < 0) f[i] += mod;
    f[i] = ((LL)f[i] * inv[i] + f[i - 1]) % mod;
  }
  printf("%d\n", (f[n] - f[n - 1] + mod) % mod);
}

int main() {
  freopen("box.in", "r", stdin);
  freopen("box.out", "w", stdout);
  Init();
  scanf("%d", &T);
  while (T --) solve();
  return 0;
}
