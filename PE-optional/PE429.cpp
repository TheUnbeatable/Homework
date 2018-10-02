#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <bitset>
using namespace std;

typedef long long LL;
const int n = 1e8;
const LL mod = 1e9 + 9;

inline LL Pow(LL x, LL exp) {
  LL res = 1;
  for (; exp; exp >>= 1) {
    if (exp & 1) res = res * x % mod;
    if (exp > 1) x = x * x % mod;
  }
  return res;
}

bitset <n + 10> notp;

int main() {
  LL ans = 1;
  for (int i = 2; i <= n; i ++)
    if (!notp[i]) {
      for (int j = i + i; j <= n; j += i) notp[j] = 1;
      LL cnt = 0, k = n;
      while (k) {
        k /= i; cnt += k;
      }
      (ans *= Pow(i, cnt * 2) + 1) %= mod;
    }
  printf("%lld\n", ans);
  return 0;
}
