#include <bits/stdc++.h>
using namespace std;

const int N = 2050;
const int mod = 1e9 + 7;

inline void Inc(int &x, int y) {
  if ((x += y) >= mod) x -= mod;
}

class WinterAndSnowmen {
private:
  int f[N][2], g[N][2];
public:
  WinterAndSnowmen() { }
  inline int getNumber(int n, int m) {
    long long ans = 0;
    for (int b = 0; (1 << b) <= m; b ++) {
      memset(f, 0, sizeof f);
      f[0][0] = 1;
      for (int i = 1; i <= max(n, m); i ++) {
        memset(g, 0, sizeof g);
        for (int j = 0; j < 2048; j ++)
          for (int k = 0; k < 2; k ++)
            if (f[j][k]) {
              if (i <= n) Inc(g[i ^ j][k], f[j][k]);
              if (i <= m) Inc(g[i ^ j][(i & (1 << b)) ? 1 - k : k], f[j][k]);
            }
        for (int j = 0; j < 2048; j ++)
          for (int k = 0; k < 2; k ++) Inc(f[j][k], g[j][k]);
      }
      for (int i = 0; i < 2048; i ++)
        if ((i >> b) == 1 && f[i][1]) ans += f[i][1];
    }
    return ans % mod;
  }
};
