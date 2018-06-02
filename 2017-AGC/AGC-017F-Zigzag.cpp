#include <cstdio>
#include <iostream>
#include <cstring>
using namespace std;

const int N = 19;
const int mod = 1e9 + 7;

int G[N + 2][N], n, m, k;
int dp[1 << N | 5], swp[1 << N | 5];

inline void Inc(int &x, int y)  {
  if ((x += y) >= mod) x -= mod;
}

inline int lowbit(int x) { return x & (- x); }

int main() {
  memset(G, -1, sizeof G);
  scanf("%d%d%d", &n, &m, &k);
  for (int i = 1, x, y; i <= k; i ++) {
    scanf("%d%d", &x, &y);
    scanf("%d", &G[x][y - 1]);
  }
  n --;
  int U = 1 << n;
  int *x = dp, *y = swp;
  x[0] = 1;
  for (int i = 1; i <= m; i ++) {
    for (int j = 0; j < n; j ++) {
      memset(y, 0, sizeof (int) * U);
      for (int k = U - 1; ~ k; k --)
        if (x[k]) {
          Inc(y[k], x[k]);
          if (!((k >> j) & 1)) Inc(y[k - lowbit(k & (U - (2 << j))) + (1 << j)], x[k]);
        }
      swap(x, y);
    }
    int key = 0, save = 0;
    for (int j = 0; j < n; j ++) {
      if (~ G[i][j]) key |= G[i][j] << j;
      else save |= 1 << j;
    }
    for (int j = 0; j < U; j ++)
      if (((j ^ key) | save) != save) x[j] = 0;
  }
  int ans = 0;
  for (int i = 0; i < U; i ++) Inc(ans, x[i]);
  printf("%d\n", ans);
  return 0;
}
