#include <cstdio>
#include <iostream>
#define ri register int
using namespace std;

const int N = 15;
const int M = 1 << N | 3;
const int mod = 1e9 + 7;

int n, m;
int G[N], f[M], cnt[M];
int tab[M][N], top[M];

inline void prt(int x) {
  if (!x) return;
  prt(x >> 1);
  cerr << (x & 1);
}

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 1, x, y; i <= m; i ++) {
    scanf("%d%d", &x, &y);
    G[x - 1] |= 1 << (y - 1);
  }
  int tot = 1;
  for (int i = 1; i <= m; i ++) tot = (tot << 1) % mod;
  for (int i = 1; i < (1 << N); i ++)
    cnt[i] = cnt[i - (i & (- i))] + 1;
  int U = 1 << n;
  for (int i = 1; i < U; i ++)
    for (int j = 0; j < n; j ++)
      if ((i >> j) & 1) tab[i][++ top[i]] = j;
  for (int i = 0; i < U; i ++)
    if ((i & 1) == ((i >> 1) & 1)) {
      for (int j = i; j; j = (j - 1) & i)
        if (f[j]) {
          ri w = i ^ j, res = 1;
          for (ri k = top[j]; k && res; k --)
            res = ((1LL << cnt[G[tab[j][k]] & w]) - 1) * res % mod;
          for (ri k = top[w]; k && res; k --)
            res = (1LL << cnt[G[tab[w][k]] & j]) * res % mod;
          f[i] = (f[i] + 1LL * f[j] * res) % mod;
        }
      f[i] ++;
    }
  printf("%d\n", (tot - f[U - 1] + mod) % mod);
  return 0;
}
