#include <bits/stdc++.h>
using namespace std;

const int N = 320;

int f[N][N], g[N][N], n, m, mod, C[N][N];

int main() {
  scanf("%d%d%d", &n, &m, &mod);
  for (int i = 0; i < N; i ++) {
    C[i][0] = 1;
    for (int j = 1; j <= i; j ++)
      C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % mod;
  }
  for (int i = 0; i <= m; i ++)
    f[1][i] = 1, g[1][i] = m - i + 1;
  for (int i = 2; i <= n + 1; i ++) {
    for (int k = 0; k <= m; k ++) {
      long long tot = 0;
      for (int j = 1; j < i; j ++)
        tot += 1ll * f[i - j][k] * g[j][k + 1] % mod * C[i - 2][j - 1] % mod;
      f[i][k] = tot % mod;
    }
    for (int k = m; k >= 0; k --)
      g[i][k] = (g[i][k + 1] + f[i][k]) % mod;
  }
  printf("%d\n", f[n + 1][0]);
  return 0;
}
