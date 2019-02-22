#include <bits/stdc++.h>
using namespace std;

const int N = 103;
const int mod = 998244353;

int dp[2][N][N], n;

inline void Inc(int &x, int y) { if ((x += y) >= mod) x -= mod; }

int main() {
  freopen("counting.in", "r", stdin);
  freopen("counting.out", "w", stdout);
  scanf("%d", &n);
  int cur = 0, nxt = 1;
  dp[cur][0][1] = 1;
  for (int i = 0; i < n * (n - 1); i ++) {
    memset(dp[nxt], 0, sizeof dp[nxt]);
    for (int k = 0; k <= n; k ++) {
      int fix = 0;
      for (int j = k; j <= n && j <= i - k + 1; j ++) {
        dp[nxt][k + 1][j] = fix;
        Inc(fix, dp[cur][k][j]);
      }
    }
    long long ans = 0;
    for (int k = 0; k <= n; k ++)
      for (int j = k; j <= n; j ++) {
        if (j * (n - 1) + (n - j) * (n - j - 1) / 2 > i)
          Inc(dp[nxt][k][j], dp[cur][k][j]);
        ans += dp[nxt][k][j];
      }
    printf("%lld ", ans % mod);
    swap(cur, nxt);
  }
  puts("");
  return 0;
}
