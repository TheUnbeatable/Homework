#include <cstdio>
#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;

const int N = 205;
const int M = 1e7 + 5;

int x[N], pos[N];

class BipartialGraph {
private :
  bool G[N][N], vis[N];
  int lkn[N];
public :
  BipartialGraph() {
    memset(G, 0, sizeof G);
  }
  inline void Add(int x, int y) {
    G[x][y] = 1;
  }
  inline bool Match(int x) {
    for (int i = 0; i < N; i ++)
      if (G[x][i] && !vis[i]) {
	vis[i] = 1;
	if (lkn[i] == -1 || Match(lkn[i])) {
	  lkn[i] = x;
	  return 1;
	}
      }
    return 0;
  }
  inline int MaxMatch() {
    int ret = 0;
    memset(lkn, -1, sizeof lkn);
    for (int i = 0; i < N; i ++) {
      memset(vis, 0, sizeof vis);
      if (Match(i)) ret ++;
    }
    return ret;
  }
} solver;

bool notp[M];
int prime[700000];

inline void  make_prime(int Max) {
  int tot = 0;
  for (int i = 2; i <= Max; i ++) {
    if (!notp[i]) prime[++ tot] = i;
    for (int j = 1; j <= tot && i * prime[j] <= Max; j ++) {
      notp[i * prime[j]] = 1;
      if (i % prime[j] == 0) break;
    }
  }
  notp[0] = notp[1] = notp[2] = 1;
}

int main() {
  int n, m = 0;
  scanf("%d", &n);
  for (int i = 1; i <= n; i ++) scanf("%d", &x[i]);
  for (int i = 1; i <= n; i ++) {
    if (i == 1 || x[i - 1] != x[i] - 1) pos[++ m] = x[i];
    if (i == n || x[i + 1] != x[i] + 1) pos[++ m] = x[i] + 1;
  }
  make_prime(pos[m] - pos[1]);
  for (int i = 1; i <= m; i ++) {
    if (pos[i] & 1) continue;
    for (int j = 1; j <= m; j ++)
      if ((pos[j] & 1) && !notp[abs(pos[j] - pos[i])]) solver.Add(i, j);
  }
  int k = solver.MaxMatch(), ev = 0, od = 0;
  for (int i = 1; i <= m; i ++) {
    if (pos[i] & 1) od ++;
    else ev ++;
  }
  ev -= k; od -= k;
  int ans = k + (ev / 2 + od / 2) * 2 + 3 * (ev & 1);
  printf("%d\n", ans);
  return 0;
}
