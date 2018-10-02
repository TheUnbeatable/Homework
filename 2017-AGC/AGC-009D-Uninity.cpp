#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
#define travel(x, y, i) for (int i = fir[x], y = e[i].to; i; i = e[i].nxt, y = e[i].to)
using namespace std;

const int N = 1e5 + 5;

struct edge {
  int nxt, to;
} e[N << 1];
int fir[N], cnt = 0;
int n, dp[N];

inline void addedge(int x, int y) {
  e[++ cnt] = (edge) { fir[x], y }; fir[x] = cnt;
}

inline int Log(int x) {
  int res = 0;
  if (x >= (1 << 16)) x >>= 16, res += 16;
  if (x >= (1 << 8)) x >>= 8, res += 8;
  if (x >= (1 << 4)) x >>= 4, res += 4;
  if (x >= (1 << 2)) x >>= 2, res += 2;
  if (x >= (1 << 1)) x >>= 1, res += 1;
  return res;
}

inline void Dfs(int x, int f) {
  int msk = 0, t = 0;
  travel(x, y, i) {
    if (y == f) continue;
    Dfs(y, x);
    int tmp = dp[y];
    for (int j = 17; j > t; j --)
      if ((msk & tmp) & (1 << j)) t = j;
    msk |= tmp;
  }
  while (msk & (1 << t)) t ++;
  msk |= (1 << t) - 1;
  msk ^= (1 << t) - 1;
  msk |= (1 << t);
  dp[x] = msk;
}

int main() {
  scanf("%d", &n);
  for (int i = 1, x, y; i < n; i ++) {
    scanf("%d%d", &x, &y);
    addedge(x, y); addedge(y, x);
  }
  Dfs(1, 0);
  printf("%d\n", Log(dp[1]));
  return 0;
}
