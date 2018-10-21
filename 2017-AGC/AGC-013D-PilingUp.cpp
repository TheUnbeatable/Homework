#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 3050;
const int mod = 1e9 + 7;

int dp[N][N][2];

inline void A(int &x, int y) {
  if ((x += y) >= mod) x -= mod;
}

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  if (n >= m) {
    int res = 1;
    for (int i = 1; i <= m + m; i ++)
      res = (res << 1) % mod;
    printf("%d\n", res);
    return 0;
  }
  dp[0][0][1] = 1;
  for (int i = 1; i <= n; i ++) dp[0][i][0] = 1;
  for (int i = 0; i < m; i ++)
    for (int j = 0; j <= n; j ++)
      for (int k = 0; k < 2; k ++) {
        if (!dp[i][j][k]) continue;
        if (j > 0) {
          A(dp[i + 1][j][k | (j == 1)], dp[i][j][k]);
          A(dp[i + 1][j - 1][k | (j == 1)], dp[i][j][k]);
        }
        if (j < n) {
          A(dp[i + 1][j][k], dp[i][j][k]);
          A(dp[i + 1][j + 1][k], dp[i][j][k]);
        }
      }
  int ans = 0;
  for (int i = 0; i <= n; i ++) A(ans, dp[m][i][1]);
  printf("%d\n", ans);
  return 0;
}
