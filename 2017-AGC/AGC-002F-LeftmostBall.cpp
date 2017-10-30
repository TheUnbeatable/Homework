#include <cstdio>
#include <iostream>
#define rs register short
using namespace std;

typedef long long LL;
const int N = 2005;
const LL mod = 1e9 + 7;

namespace MathCal {
#define ri register int
  static const int R = N * N;
  LL fac[R], inv[R];
  inline LL pow(LL x, LL e) {
    LL res = 1;
    for (; e; e >>= 1, x = x * x % mod)
      if (e & 1) res = res * x % mod;
    return res;
  }
  inline void Init(int n) {
    for (ri i = fac[0] = 1; i <= n; i ++) fac[i] = fac[i - 1] * i % mod;
    inv[n] = pow(fac[n], mod - 2);
    for (ri i = n; i; i --) inv[i - 1] = inv[i] * i % mod;
  }
  inline LL Co(int x, int y) {
    if (y > x) return 0;
    return fac[x] * inv[y] % mod * inv[x - y] % mod;
  }
#undef ri
}
using namespace MathCal;

LL dp[N][N];

int main() {
  int n, k;
  scanf("%d%d", &n, &k);
  if (k == 1 || n == 1) return !puts("1");
  MathCal::Init(n * k);
  dp[0][0] = 1;
  for (rs i = 1; i <= n; i ++)
    for (rs j = 0; j <= i; j ++) {
      dp[i][j] = dp[i - 1][j];
      if (j) {
	dp[i][j] += Co(n * k - i - (k - 1) * (j - 1) - 1, k - 2) * dp[i][j - 1] % mod;
	if (dp[i][j] >= mod) dp[i][j] -= mod;
      }
    }
  printf("%lld\n", dp[n][n] * fac[n] % mod);
  return 0;
}
