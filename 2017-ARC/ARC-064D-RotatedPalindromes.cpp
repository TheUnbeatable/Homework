#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;

typedef long long LL;
const LL mod = 1e9 + 7;

inline LL pow(LL x, LL exp) {
  LL res = 1;
  for (; exp; exp >>= 1, x = x * x % mod)
    if (exp & 1) res = res * x % mod;
  return res;
}

LL dp[5005], arr[5005];

int main() {
  LL n, k, m = 0;
  scanf("%lld%lld", &n, &k);
  for (LL i = 1; i * i <= n; i ++)
    if (n % i == 0) {
      arr[++ m] = i;
      if (i * i != n) arr[++ m] = n / i;
    }
  sort(arr + 1, arr + m + 1);
  LL ans = 0;
  for (int i = 1; i <= m; i ++) {
    dp[i] = pow(k, (arr[i] + 1) / 2);
    for (int j = 1; j < i; j ++)
      if (arr[i] % arr[j] == 0) {
	dp[i] -= dp[j];
	if (dp[i] < 0) dp[i] += mod;
      }
    if (arr[i] & 1) ans += arr[i] * dp[i] % mod;
    else ans += (arr[i] / 2) * dp[i] % mod;
    if (ans >= mod) ans -= mod;
  }
  printf("%lld\n", ans);
  return 0;
}
