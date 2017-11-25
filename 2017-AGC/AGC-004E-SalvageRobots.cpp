#include <cstdio>
#include <iostream>
#define ri register int
using namespace std;
 
typedef long long LL;
const int N = 102;

char ch[N][N];
short le[N][N], up[N][N], dp[N][N][N][N];
 
inline void upd(short &x, short y) {
  if (x < y) x = y;
}
 
int main() {
  int n, m, ex, ey;
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; i ++) {
    scanf("%s", ch[i] + 1);
    for (int j = 1; j <= m; j ++) {
      le[i][j] = le[i][j - 1];
      up[i][j] = up[i - 1][j];
      if (ch[i][j] == 'o') le[i][j] ++, up[i][j] ++;
      if (ch[i][j] == 'E') ex = i, ey = j;
    }
  }
  short t, ans = 0;
  for (ri U = ex; U; U --)
    for (ri D = ex; D <= n; D ++)
      for (ri L = ey; L; L --)
	for (ri R = ey; R <= m; R ++) {
	  t = dp[U][D][L][R];
	  ans = max(ans, t);
	  if (U - 1 > D - ex) upd(dp[U - 1][D][L][R], t + le[U - 1][min(R, m - (ey - L))] - le[U - 1][max(L - 1, R - ey)]);
	  if (n - D > ex - U) upd(dp[U][D + 1][L][R], t + le[D + 1][min(R, m - (ey - L))] - le[D + 1][max(L - 1, R - ey)]);
	  if (L - 1 > R - ey) upd(dp[U][D][L - 1][R], t + up[min(D, n - (ex - U))][L - 1] - up[max(U - 1, D - ex)][L - 1]);
	  if (m - R > ey - L) upd(dp[U][D][L][R + 1], t + up[min(D, n - (ex - U))][R + 1] - up[max(U - 1, D - ex)][R + 1]);
	}
  cout << ans << endl;
  return 0;
}
