#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

typedef long long LL;
const LL n = 1e15;
const LL mod = 1e9;

inline LL sum(LL x) {
  x %= mod;
  LL tmp = x * (x + 1) / 2;
  if (tmp % 3)
    return (tmp % mod) * ((x + x + 1) / 3) % mod;
  else
    return ((tmp / 3) % mod) * (x + x + 1) % mod;
}

int main() {
  LL ans = 0;
  for (LL i = 1, j = 1; i <= n; i = j + 1) {
    j = n / (n / i); j = min(j, n);
    (ans += (sum(j) - sum(i - 1)) * ((n / i) % mod)) %= mod;
  }
  printf("%lld\n", (ans + mod) % mod);
  return 0;
}
