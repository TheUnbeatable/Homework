#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

typedef long long LL;
const int N = 105;
const LL mod = 1000000033;

int dp[N][N], n = 100, pw[N * N], C[N][N];

inline int calc(int i, int j) { return pw[i * j]; }

inline void Init() {
  for (int i = pw[0] = 1; i <= n * n; i ++)
    pw[i] = (pw[i - 1] << 1) % mod;
  for (int i = 0; i <= n; i ++) {
    C[i][0] = 1;
    for (int j = 1; j <= i; j ++)
      C[i][j] = ( C[i - 1][j - 1] + C[i - 1][j] ) % mod;
  }
}

int main() {
  Init();
  LL ans = 0;
  for (int i = 0; i <= n; i ++)
    for (int j = 0; j <= n; j ++) {
      if (!i || !j) dp[i][j] = (i + j <= 1);
      else {
        LL op = 0;
        for (int k = 1; k <= i; k ++)
          for (int l = 0; l <= j; l ++)
            if (k != i || l != j) {
              ( op += 1ll * C[i - 1][k - 1] * C[j][l] % mod * calc(i - k, j - l) % mod * dp[k][l] )  %= mod;
            }
        dp[i][j] = calc(i, j) - op;
        if (dp[i][j] < 0) dp[i][j] += mod;
        ans += dp[i][j];
      }
    }
  printf("%lld\n", ans % mod);
  return 0;
}
