#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
const int N = 1005;

struct Object {
  int x, y, v;
} a[N];
int f[N][N], g[N][N];

inline bool cmp(const Object c, const Object &d) { return c.y == d.y ? c.x < d.x : c.y < d.y; }

struct BIT {
  int bit[N]; bool rev;
  BIT() { memset(bit, 0, sizeof bit); rev = 0; }
  inline int Max(int x) {
    x ++; if (rev) x = N - x; int r = 0;
    for (; x > 0; x -= x & (- x)) r = max(r, bit[x]);
    return r;
  }
  inline void Upd(int x, int v) {
    x ++; if (rev) x = N - x;
    for (; x < N; x += x & (- x)) bit[x] = max(bit[x], v);
  }
} sma[N << 1], big[N << 1];

class FoxSearchingRuins {
public :
  inline LL DP(int LR, int n, int Tx, int Ty, int goal) {
    int X;
    LL ans = 1e18;
    for (int i = (N << 1) - 1; i >= 0; i --) big[i].rev = 1;
    for (int i = 1, j = 1; i <= n; i = j) {
      while (a[j].y == a[i].y && j <= n) j ++;
      for (int k = i; k < j; k ++) {
	X = a[k].x;
	for (int l = 0; l <= LR; l ++) {
	  f[k][l] = max(sma[N + l - X].Max(X), big[X + l].Max(X)) + a[k].v;
	  if (l == 0) f[k][l] = max(f[k][l], a[k].v);
	  g[k][l] = f[k][l];
	}
      }
      for (int k = j - 2; k >= i; k --) {
	X = a[k + 1].x - a[k].x;
	for (int l = X; l <= LR; l ++)
	  f[k][l] = max(f[k][l], f[k + 1][l - X] + a[k].v);
      }
      for (int k = i + 1; k < j; k ++) {
	X = a[k].x - a[k - 1].x;
	for (int l = X; l <= LR; l ++)
	  g[k][l] = max(g[k][l], g[k - 1][l - X] + a[k].v);
      }
      for (int k = i; k < j; k ++) {
	X = a[k].x;
	for (int l = 0; l <= LR; l ++) {
	  f[k][l] = max(f[k][l], g[k][l]);
	  sma[N + l - X].Upd(X, f[k][l]);
	  big[X + l].Upd(X, f[k][l]);
	}
      }
    }
    for (int i = 1; i <= n; i ++)
      for (int j = 0; j <= LR; j ++)
	if (f[i][j] >= goal) ans = min(ans, j * Tx + 1LL * a[i].y * Ty);
    return ans == 1e18 ? -1 : ans;
  }
  inline LL theMinTime(int W, int H, int jewelCount, int LR, int goalValue, int timeX, int timeY, vector <int> seeds) {
    a[1].x = (1LL * seeds[1] * seeds[0] + seeds[2]) % W;
    a[1].y = (1LL * seeds[4] * seeds[3] + seeds[5]) % H;
    a[1].v = (1LL * seeds[7] * seeds[6] + seeds[8]) % seeds[9];
    for (int i = 2; i <= jewelCount; i ++) {
      a[i].x = (1LL * seeds[1] * a[i-1].x + seeds[2]) % W;
      a[i].y = (1LL * seeds[4] * a[i-1].y + seeds[5]) % H;
      a[i].v = (1LL * seeds[7] * a[i-1].v + seeds[8]) % seeds[9];
    }
    sort(a + 1, a + jewelCount + 1, cmp);
    int n = 1;
    for (int i = 2; i <= jewelCount; i ++) {
      if (a[i].x != a[i - 1].x || a[i].y != a[i - 1].y) a[++ n] = a[i];
      else a[n].v += a[i].v;
    }
    return DP(LR, n, timeX, timeY, goalValue);
  }
};
