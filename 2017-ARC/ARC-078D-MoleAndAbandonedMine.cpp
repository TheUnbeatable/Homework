#include <cstdio>
#include <iostream>
#include <cstring>
#include <ctime>
#define rus register unsigned short
#define rs register short
using namespace std;

const int N = 15;

int G[N][N], dp[N][1 << N], cost[N][1 << N], ss1[1 << N][1 << 5], ss2[1 << N][1 << 5], ss3[1 << N][1 << 5];
int n, m, base1 = (1 << 5) - 1, Base1 = 1 << 5, base2 = (1 << 10) - 1, Base2 = 1 << 10;

inline void upd(int &x, int y) {
  if (x == -1) x = y;
  else x = min(x, y);
}

inline int set_set(int x, int y) {
  return ss1[x][y & base1] + ss2[x][(y >> 5) & base1] + ss3[x][y >> 10];
}

inline int calc(int x, int y) {
  if (x & y) return 0;
  int ret = 0;
  for (rs i = 0; i < n; i ++)
    if (x & (1 << i)) ret += cost[i][y];
  return ret;
}

int main() {
  memset(dp, -1, sizeof dp);
  scanf("%d%d", &n, &m);
  for (int i = 1, x, y, z; i <= m; i ++) {
    scanf("%d%d%d", &x, &y, &z);
    x --; y --;
    G[x][y] = G[y][x] = z;
  }
  int t = 1 << n;
  int st = clock();
  for (rus s = 1; s < t; s ++) {
    for (rs i = 0; i < n; i ++) cost[i][s] = cost[i][s - (s & (- s))];
    for (rs i = 0; i < n; i ++)
      if (s & (1 << i)) {
	for (rs j = 0; j < n; j ++) cost[j][s] += G[i][j];
	break;
      }
  }
  for (rus s = 1; s < t; s ++) {
    for (rus i = 1; i < Base1 && i < t; i ++) ss1[s][i] = calc(s, i);
    for (rus i = Base1, j = 1; i < t && i < Base2; i += Base1, j ++) ss2[s][j] = calc(s, i);
    for (rus i = Base2, j = 1; i < t; i += Base2, j ++) ss3[s][j] = calc(s, i);
  }
  dp[0][1] = 0;
  int in[N], out[N], cntin, cntout;
  for (rus s = 1; s < t; s += 2) {
    rus u = s ^ (t - 1);
    cntin = cntout = 0;
    for (rs i = 0; i < n; i ++) {
      if (s & (1 << i)) in[cntin ++] = i;
      else out[cntout ++] = i;
    }
    for (rs a = 0, i = in[a]; a < cntin; a ++, i = in[a]) {
      if (dp[i][s] == -1) continue;
      for (rs b = 0, j = out[b]; b < cntout; b ++, j = out[b])
	if (!(s & (1 << j)) && G[i][j]) upd(dp[j][s | (1 << j)], dp[i][s] + cost[j][s ^ (1 << i)]);
      for (rus v = u; v; v = (v - 1) & u)
	upd(dp[i][v | s], dp[i][s] + set_set(v, s ^ (1 << i)));
    }
  }
  printf("%d\n", dp[n - 1][t - 1]);
  return 0;
}
