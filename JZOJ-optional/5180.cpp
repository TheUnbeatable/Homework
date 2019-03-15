#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
const int N = 2020;
const int mod = 1e9 + 7;

inline LL Pow(LL x, LL exp = mod - 2) {
  LL res = 1;
  for (; exp; exp >>= 1, x = x * x % mod)
    if (exp & 1) res = res * x % mod;
  return res;
}

int w[N], fac[N], f[N], n;

int main() {
  freopen("hehe.in", "r", stdin);
  freopen("hehe.out", "w", stdout);
  scanf("%d", &n);
  if (n == 1) {
    puts("0"); return 0;
  }
  LL sum = 0, prod = 1;
  for (int i = fac[0] = 1; i <= n; i ++) {
    scanf("%d", &w[i]);
    fac[i] = (LL)fac[i - 1] * i % mod;
    sum += w[i];
    prod = prod * w[i] % mod;
  }
  sum %= mod;
  f[0] = 1;
  for (int i = 1; i <= n; i ++)
    for (int j = i; j; j --)
      f[j] = (f[j] + (LL)f[j - 1] * w[i]) % mod;
  LL ans = 0;
  for (int i = 0; i <= n - 2; i ++)
    ans += f[i] * Pow(sum, n - 2 - i) % mod * Pow(fac[n - 2 - i]) % mod;
  ans = ans % mod * prod % mod * fac[n - 2] % mod;
  printf("%lld\n", ans);
  return 0;
}
