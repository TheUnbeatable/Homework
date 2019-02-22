#include <bits/stdc++.h>
using namespace std;

const int N = 3003;
const int mod = 998244353;
const long long sqr = 6ll * mod * mod;

int C[N][N], pw[N * N];

inline int add(int x, int y) {
  return (x += y) >= mod ? x - mod : x;
}

inline void Init() {
  for (int i = 0; i < N; i ++) {
    C[i][0] = 1;
    for (int j = 1; j <= i; j ++)
      C[i][j] = add(C[i - 1][j - 1], C[i - 1][j]);
  }
  int g = N * N;
  for (int i = pw[0] = 1; i < g; i ++)
    pw[i] = add(pw[i - 1], pw[i - 1]);
}

int n, m, a, b, f[N], g[N];

inline void solve() {
  f[a] = g[b] = 1;
  for (int j = a + 1; j <= n; j ++) {
    long long tmp = 1;
    for (int i = a; i < j; i ++) {
      tmp -= (long long) C[j][i] * f[i];
      if (tmp < 0) tmp += sqr;
    }
    f[j] = tmp % mod;
  }
  for (int j = b + 1; j <= m; j ++) {
    long long tmp = 1;
    for (int i = b; i < j; i ++) {
      tmp -= (long long) C[j][i] * g[i];
      if (tmp < 0) tmp += sqr;
    }
    g[j] = tmp % mod;
  }
  long long ans = 0;
  for (int i = a; i <= n; i ++)
    f[i] = (long long) f[i] * C[n][i] % mod;
  for (int i = b; i <= m; i ++)
    g[i] = (long long) g[i] * C[m][i] % mod;
  for (int i = a; i <= n; i ++)
    for (int j = b; j <= m; j ++) {
      ans += (long long) f[i] * g[j] % mod * pw[(n - i) * (m - j)];
      if (ans >= sqr) ans -= sqr;
    }
  printf("%lld\n", ans % mod);
}

int main() {
  Init();
  while (scanf("%d%d%d%d", &n, &m, &a, &b) != EOF) solve();
  return 0;
}
