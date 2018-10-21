#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;

const int N = 55;
const int mod = 1e9 + 7;
typedef vector <int> vi;

struct P {
  int x, y, id;
  P() : x(0), y(0), id(0) {}
  P(int _x, int _y, int _id) : x(_x), y(_y), id(_id) {}
  inline P operator+ (const P &o) const {
    return P(x + o.x, y + o.y, 0);
  }
  inline P operator- (const P &o) const {
    return P(x - o.x, y - o.y, 0);
  }
  inline int operator^ (const P &o) const {
    return x * o.y - y * o.x;
  }
} s[N], t[N][N];

int n, dp[N][N][N][N];

inline int DP(int l, int r, int lf, int rf, int d) {
  if (l >= r) return 1;
  int &res = dp[l][r][lf][rf];
  if (res != -1) return res;
  res = 0;
  P *a = t[d];
  int n = r - l + 1, id = 1;
  for (int i = 2; i <= n; i ++)
    if (a[id].y < a[i].y) id = i;
  for (int i = l, al, ar; i <= r; i ++) {
    al = dp[l][i - 1][lf][a[id].id];
    ar = dp[i + 1][r][a[id].id][rf];
    if (!al || !ar) continue;
    if (al == -1) {
      int ptr = 0;
      P *b = t[d + 1];
      for (int j = 1; j <= n; j ++)
        if ( ( ( a[id] - s[i] ) ^ ( a[j] - s[i] ) ) > 0 ) b[++ ptr] = a[j];
      if (ptr != i - l) continue;
      al = DP(l, i - 1, lf, a[id].id, d + 1);
    }
    if (ar == -1) {
      int ptr = 0;
      P *b = t[d + 1];
      for (int j = 1; j <= n; j ++)
        if ( ( ( a[id] - s[i] ) ^ ( a[j] - s[i] ) ) < 0 ) b[++ ptr] = a[j];
      if (ptr != r - i) continue;
      ar = DP(i + 1, r, a[id].id, rf, d + 1);
    }
    res = (res + 1ll * al * ar) % mod;
  }
  return res;
}

struct CoastGuard {
public:
  inline int count(vi d, vi x, vi y) {
    :: n = d.size();
    sort(d.begin(), d.end());
    for (int i = 0; i < :: n; i ++) s[i + 1] = P(d[i], 0, 0);
    for (int i = 0; i < :: n; i ++) t[0][i + 1] = P(x[i], y[i], i + 1);
    memset(dp, -1, sizeof dp);
    return :: DP(1, n, 0, 0, 0);
  }
};
