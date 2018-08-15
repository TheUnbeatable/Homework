#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

typedef long long LL;
const int N = 3050;

int n;
LL f[N][N], g[N], fix[N], a[N];

int main() {
#ifdef ONLINE_JUDGE
  freopen("ebola.in", "r", stdin);
  freopen("ebola.out", "w", stdout);
#endif
  while (scanf("%d", &n), n) {
    for (int i = 1; i <= n; i ++) {
      scanf("%lld", &a[i]);
      fix[i] = fix[i - 1] + a[i];
    }
    for (int r = 1; r <= n; r ++) {
      LL lst = f[r][r] = 0;
      for (int l = r - 1; l; l --)
        f[l][r] = ( lst += (fix[r] - fix[l]) + min( fix[r] - fix[l], a[l] * 3 * (r - l) ) );
    }
    g[n + 1] = 0;
    for (int i = n; i; i --) {
      LL cur = 0, res = 8e18;
      for (int j = i; j <= n; j ++) {
        cur += a[j] * (j - i) * 2;
        res = min( res, g[j + 1] + 2 * (j - i + 1) * (fix[n] - fix[j]) + cur );
      }
      for (int j = i; j <= n; j ++)
        res = min( res, f[i][j] + (4 * (j - i) + 2) * (fix[n] - fix[j]) + g[j + 1] );
      g[i] = res;
    }
    printf("%lld\n", g[1]);
  }
  return 0;
}
