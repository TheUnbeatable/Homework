#include <cstdio>
#include <iostream>
using namespace std;

typedef long long LL;
const int N = 3005;
LL mod = 1e9 + 7;

int n, m, r[N], pref[N];
LL dp[N][N];
char s[N];

inline void modadd(LL &x, LL y) {
  x += y;
  if (x >= mod) x -= mod;
}

int main() {
  scanf("%d%d", &n, &m);
  scanf("%s", s + 1);
  for (int i = 1; i <= n; i ++) {
    r[i] = i;
    pref[i] = pref[i - 1] + s[i] - '0';
  }
  for (int i = 1, x, y; i <= m; i ++) {
    scanf("%d%d", &x, &y);
    r[x] = max(r[x], y);
  }
  int c = 0, R = 0, t;
  dp[0][0] = 1;
  for (int i = 1; i <= n; i ++) {
    t = 0;
    if (R < r[i]) {
      c += (t = pref[r[i]] - pref[R]);
      R = r[i];
    }
    if (i == R)
      modadd(dp[i][0], dp[i - 1][0] + dp[i - 1][1]);
    else {
      for (int j = t - 1; j <= c && j <= R - i; j ++) {
  	if (j >= t) modadd(dp[i][j], dp[i - 1][j - t]);
  	if (j >= t - 1) modadd(dp[i][j], dp[i - 1][j - t + 1]);
      }
    }
  }
  printf("%lld\n", dp[n][0]);
  return 0;
}
