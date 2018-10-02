#include <cstdio>
#include <iostream>
#include <cstdlib>
using namespace std;

typedef long long LL;
const int N = 2005;
const LL mod = 1000000007LL;

int n, k;
LL dp[N][N], C[N][N], pref[N];

inline LL pow(LL x, LL exp) {
  if (exp < 0) return 1;
  LL res = 1;
  for (; exp; exp >>= 1, x = x * x % mod)
    if (exp & 1) res = res * x % mod;
  return res;
}

inline void pre() {
  for (int i = 0; i < N; i ++) {
    C[i][0] = 1;
    for (int j = 1; j <= i; j ++) {
      C[i][j] = C[i - 1][j - 1] + C[i - 1][j];
      if (C[i][j] >= mod) C[i][j] -= mod;
    }
  }
}

inline LL DP() {
  pref[0] = 1;
  for (int i = 2; i <= n - 1; i ++) {
    for (int j = 1; j < i; j ++) {
      pref[j] = pref[j - 1] + dp[i - 1][j];
      if (pref[j] >= mod) pref[j] -= mod;
      dp[i][j] = pref[j];
    }
  }
  LL ans = 1;
  for (int i = 1; i <= k - 1; i ++) {
    ans += dp[n - 1][i];
    if (ans >= mod) ans -= mod;
  }
  return ans;
}

int main() {
  pre();
  scanf("%d%d", &n, &k);
  if (k == 1) return printf("%lld\n", pow(2LL, n - 2)), 0;
  if (k == 2) {
    LL ans = pow(2LL, n - k - 1) * (n - 1) % mod;
    return printf("%lld\n", ans), 0;
  }
  LL ans = DP();
  ans = ans * pow(2LL, n - k - 1) % mod;
  printf("%lld\n", ans);
  return 0; 
}
