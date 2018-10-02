#include <cstdio>
#include <iostream>
using namespace std;

const int N = 305;
const int mod = 1e9 + 7;

int dp[N][N][N], n, m;
int mx[N][4], mn[N][4];

inline void modadd(int &x, int y) {
  x += y;
  if (x >= mod) x -=  mod;
}

inline bool legal(int R, int G, int B) {
  if (R == G && R) return 0;
  if (R == B && R) return 0;
  if (G == B && G) return 0;
  int now = max(R, max(G, B));
  for (int i = 1; i <= 3; i ++)
    if (mn[now][i] &&
	((R >= mn[now][i]) + (G >= mn[now][i]) + (B >= mn[now][i]) != i
	|| (R >= mx[now][i]) + (G >= mx[now][i]) + (B >= mx[now][i]) != i)) return 0;
  return 1;
}

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 1, l, r, x; i <= m; i ++) {
    scanf("%d%d%d", &l, &r, &x);
    if (mn[r][x]) mn[r][x] = min(mn[r][x], l);
    else mn[r][x] = l;
    mx[r][x] = max(mx[r][x], l);
  }
  int now;
  dp[0][0][0] = 1;
  for (int R = 0; R < n; R ++)
    for (int G = 0; G < n; G ++)
      for (int B = 0; B < n; B ++) {
	if (!legal(R, G, B) || !dp[R][G][B]) continue;
	now = max(R, max(G, B)) + 1;
	modadd(dp[now][G][B], dp[R][G][B]);
	modadd(dp[R][now][B], dp[R][G][B]);
	modadd(dp[R][G][now], dp[R][G][B]);
      }
  int ans = 0;
  for (int i = 0; i < n; i ++)
    for (int j = 0; j < n; j ++) {
      if (legal(n, i, j)) modadd(ans, dp[n][i][j]);
      if (legal(i, n, j)) modadd(ans, dp[i][n][j]);
      if (legal(i, j, n)) modadd(ans, dp[i][j][n]);
    }
  printf("%d\n", ans);
  return 0;
}
