#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 2005;

char G[N][N];
int lx[N], rx[N], ly[N], ry[N], n, m;
int fx[N], dp[N][N];

inline void revX() {
  for (int i = 1; i <= n; i ++) {
    if (!lx[i]) continue;
    swap(lx[i], rx[i]);
    lx[i] = m + 1 - lx[i];
    rx[i] = m + 1 - rx[i];
  }
  for (int i = 1, j = m; i < j; i ++, j --) {
    swap(ly[i], ly[j]); swap(ry[i], ry[j]);
  }
}

inline void revY() {
  for (int i = 1; i <= m; i ++) {
    if (!ly[i]) continue;
    swap(ly[i], ry[i]);
    ly[i] = n + 1 - ly[i];
    ry[i] = n + 1 - ry[i];
  }
  for (int i = 1, j = n; i < j; i ++, j --) {
    swap(lx[i], lx[j]); swap(rx[i], rx[j]);
  }
}

inline int calc(int x, int y) {
  if (!lx[x]) return 0;
  if (y < lx[x] || y > rx[x]) return 0;
  return dp[x][y];
}

inline int DP() {
  fx[0] = N;
  for (int i = 1; i <= n; i ++)
    fx[i] = min(fx[i - 1], lx[i] ? lx[i] : N);
  int res = 0;
  for (int i = 1; i <= n; i ++) {
    if (!lx[i]) continue;
    for (int j = lx[i]; j <= rx[i]; j ++) {
      if (j <= fx[i - 1]) dp[i][j] = 0;
      else dp[i][j] = calc(ly[j], lx[i]) + 1;
      res = max(res, dp[i][j]);
    }
  }
  return res;
}

int main() {
#ifdef ONLINE_JUDGE
  freopen("jinxiety.in", "r", stdin);
  freopen("jinxiety.out", "w", stdout);
#endif
  for (; ; ) {
    scanf("%d%d", &n, &m);
    if (!n && !m) break;
    for (int i = 1; i <= n; i ++) {
      lx[i] = rx[i] = 0;
      scanf("%s", G[i] + 1);
      for (int j = 1; j <= m; j ++)
        if (G[i][j] == '#') { lx[i] = j; break; }
      for (int j = m; j; j --)
        if (G[i][j] == '#') { rx[i] = j; break; }
    }
    for (int j = 1; j <= m; j ++) {
      ly[j] = ry[j] = 0;
      for (int i = 1; i <= n; i ++)
        if (G[i][j] == '#') { ly[j] = i; break; }
      for (int i = n; i; i --)
        if (G[i][j] == '#') { ry[j] = i; break; }
    }
    int ans = 0;
    ans = max(ans, DP());
    revX(); ans = max(ans, DP());
    revY(); ans = max(ans, DP());
    revX(); ans = max(ans, DP());
    printf("%d\n", ans);
  }
  return 0;
}
