#include <cstdio>
#include <iostream>
#define rep(i, x, y) for (int i = (x); i <= (y); i ++)
#define drep(i, x, y) for (int i = (x); i >= (y); i --)
using namespace std;

typedef long long LL;
const int N = 2005;
const LL mod = 924844033;

LL C[N][N], dp[N], fac[N];

inline void pre() {
  rep(i, 0, N - 1) {
    C[i][0] = 1;
    rep(j, 1, i) {
      C[i][j] = C[i - 1][j - 1] + C[i - 1][j];
      if (C[i][j] >= mod) C[i][j] -= mod;
    }
  }
}

int main() {
  pre();
  int n, k, t;
  cin >> n >> k;
  dp[0] = 1;
  rep(i, 1, k) {
    t = (n - i) / k + 1;
    drep(k, n, 1) {
      rep(j, 1, min(k, t >> 1)) {
	(dp[k] += dp[k - j] * C[t - j][j]) %= mod;
      }
    }
    drep(k, n, 1) {
      rep(j, 1, min(k, t >> 1)) {
	(dp[k] += dp[k - j] * C[t - j][j]) %= mod;
      }
    }
  }
  fac[0] = 1;
  rep(i, 1, n) fac[i] = fac[i - 1] * i % mod;
  LL ans = 0, sgn = 1;
  rep(i, 0, n) {
    ans = (ans + sgn * dp[i] * fac[n - i] % mod + mod) % mod;
    sgn *= -1;
  }
  cout << ans << endl;
  return 0;
}
