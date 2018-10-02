#include <cstdio>
#include <iostream>
#include <cstring>
using namespace std;

const int N = 2050;
const int mod = 1e9 + 7;

int n, m, K, dp[N], sum[N];

int main() {
  scanf("%d%d%d", &n, &m, &K);
  int t = (n + m - 1) / (K - 1);
  int lst = 1, cur = 0;
  long long ans = 0;
  for (int i = 0; i <= m; i ++) sum[i] = 1;
  for (int i = 1; i <= t; i ++) {
    for (int j = 0; j <= m; j ++) {
      dp[j] = sum[j] - (j >= K ? sum[j - K] : 0);
      if (dp[j] < 0) dp[j] += mod;
      int tm = i * (K - 1) - j;
      if (tm >= 0 && tm < n && tm % (K - 1) == (n - 1) % (K - 1) && j % (K - 1) == m % (K - 1))
        ans += dp[j] - (sum[j] - sum[j - 1]);
    }
    sum[0] = dp[0];
    for (int j = 1; j <= m; j ++)
      sum[j] = (sum[j - 1] + dp[j]) % mod;
  }
  printf("%lld\n", (ans % mod + mod) % mod);
  return 0;
}
