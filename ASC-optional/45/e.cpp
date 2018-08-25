#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
#define calc(i, j) ( ( a * i + b * j + c * (i ^ j) ) % mod )
using namespace std;

const int N = 1 << 12 | 5;

int a, b, c, tmp, mod, n;
int dp[N][N], path[N][N], res[N];

int main() {
#ifdef ONLINE_JUDGE
  freopen("elegant.in", "r", stdin);
  freopen("elegant.out", "w", stdout);
#endif
  while (scanf("%d", &n), n) {
    scanf("%d%d%d%d", &a, &b, &c, &mod);
    for (int i = 1; i < n; i ++)
      memset(dp[i], 0x3f, sizeof (int) * n);
    for (int p = 0, h; p < n - 1; p ++) {
      for (h = 0; ; h ++)
        if (!((p >> h) & 1)) break;
      for (int i = 0; i < n; i ++) {
        int BEG = ((i >> h) ^ 1) << h;
        for (int j = BEG; j < BEG + (1 << h); j ++)
          if ( ( tmp = dp[p][i] + calc(i, j) ) < dp[p + 1][j] ) {
            dp[p + 1][j] = tmp; path[p + 1][j] = i;
          }
      }
    }
    int pos = 0, best = 2e9;
    for (int i = 0; i < n; i ++)
      if (best > dp[n - 1][i]) {
        pos = i; best = dp[n - 1][i];
      }
    res[n - 1] = pos;
    for (int i = n - 1; i; i --)
      res[i - 1] = pos = path[i][pos];
    printf("%d\n", best);
    for (int i = 0; i < n; i ++)
      printf("%d%c", res[i], i == n - 1 ? '\n' : ' ');
  }
  return 0;
}
