#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
const int mod = 998244353;

inline LL Pow(LL x, LL exp = mod - 2) {
  LL res = 1;
  for (; exp; exp >>= 1, x = x * x % mod)
    if (exp & 1) res = res * x % mod;
  return res;
}

int n, k, inv[10100000];
LL T;

int main() {
  freopen("set.in", "r", stdin);
  freopen("set.out", "w", stdout);
  scanf("%d%d%lld", &n, &k, &T);
  if (T == 1) {
    puts("1");
    return 0;
  }
  for (int i = inv[0] = 1; i <= k; i ++)
    inv[i] = (LL) inv[i - 1] * i % mod;
  LL fa = Pow(inv[k]);
  for (int i = k; i; i --) {
    inv[i] = inv[i - 1] * fa % mod;
    fa = fa * i % mod;
  }
  n --; k --;
  LL iT = Pow(T), y, x, iTn1 = Pow(iT, n + 1);
  LL low = Pow(T - 1), C = iTn1;
  y = (mod + 1 - iTn1 % mod) * Pow(mod + 1 - iT) % mod;
  for (int i = 1; i <= k; i ++, y = x) {
    C = C * (n - i + 2) % mod * inv[i] % mod;
    x = (y - T * C % mod) * low % mod;
  }
  C = C * Pow(iTn1) % mod;
  k ++;
  C = C * (n - k + 2) % mod * inv[k] % mod;
  y = (y % mod + mod) % mod;
  printf("%lld\n", y * Pow(T, n + 1) % mod * Pow(C) % mod);
  return 0;
}
