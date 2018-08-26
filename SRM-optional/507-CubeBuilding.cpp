#include <cstdio>
#include <iostream>
#define ri register int
using namespace std;

typedef long long LL;
const int N = 26;
const LL mod = 1e9 + 7;

class CubeBuilding {
private :
  LL C[100][100];
  int dp[N][N][N][N * 2], f[N][N * 2], res[N][N * 2];
public :
  inline void pre() {
    for (int i = 0; i < 100; i ++) {
      C[i][0] = 1;
      for (int j = 1; j <= i; j ++) {
        C[i][j] = C[i - 1][j - 1] + C[i - 1][j];
        if (C[i][j] >= mod) C[i][j] -= mod;
      }
    }
  }
  inline int getCount(int R, int G, int B, int N) {
    pre();
    dp[0][0][0][0] = 1;
    int n = max(R, max(G, B)), m = max(R + G, B + max(R, G));
    for (ri i = 0; i < N; i ++)
      for (ri h = 0; h <= n; h ++)
        for (ri j = h; j <= n; j ++)
          for (ri k = 0; k <= m; k ++) {
            if (!dp[i][h][j][k]) continue;
            register LL val = dp[i][h][j][k];
            for (ri a = 0; a + j <= n; a ++)
              for (ri b = 0; b + k <= m && b <= h; b ++) {
                if (a + b > h)
                  dp[i + 1][a + b][j + a][k + b] = (dp[i + 1][a + b][j + a][k + b] + val * C[h][b]) % mod;
                else
                  dp[i + 1][h][j + a][k + b] = (dp[i + 1][h][j + a][k + b] + val * C[a + b][b]) % mod;
              }
          }
    for (ri h = 0; h <= n; h ++)
      for (ri j = h; j <= n; j ++)
        for (ri k = 0; k <= m; k ++) (f[j][k] += dp[N][h][j][k]) %= mod;
    res[0][0] = 1;
    for (ri i = 1; i <= N; i ++)
      for (ri j = n; j >= 0; j --)
        for (ri k = m; k >= 0; k --) {
          LL val = 0;
          for (ri a = 0; a <= j; a ++)
            for (ri b = 0; b <= k; b ++)
              (val += (LL)res[a][b] * f[j - a][k - b]) %= mod;
          res[j][k] = val;
        }
    LL ans = 0;
    (ans += res[R][G + B] * C[G + B][G]) %= mod;
    (ans += res[G][R + B] * C[R + B][R]) %= mod;
    (ans += res[B][R + G] * C[R + G][R]) %= mod;
    return (int)ans;
  }
};
