#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

const int mod = 1e9 + 7;

class LitPanels {
private:
  int dp[2][17][5];
  int nn, mm, xx, yy;
  inline bool in1(int x, int y) {
    if (x <= nn && y <= mm) return 1;
    return (x >= xx - nn + 1) && (y >= yy - mm + 1);
  }
  inline bool in2(int x, int y) {
    return in1(x, yy - y + 1);
  }
  inline void Inc(int &x, int y) {
    if ((x += y) >= mod) x -= mod;
  }
  inline int calc(int x, int y) {
    xx = x; yy = y;
    memset(dp, 0, sizeof dp);
    int cur = 0, nxt = 1;
    dp[cur][0][0] = 1;
    for (int i = 1; i <= x; i ++)
      for (int j = 1; j <= y; j ++) {
        memcpy(dp[nxt], dp[cur], sizeof dp[nxt]);
        int msk = 0, ss = 0;
        if (i == 1) msk |= 1;
        if (i == x) msk |= 8;
        if (j == 1) msk |= 2;
        if (j == y) msk |= 4;
        if (!in1(i, j)) ss |= 1;
        if (!in2(i, j)) ss |= 2;
        for (int bo = 0; bo < 16; bo ++) {
          if (i > 1 && !(bo & 1)) continue;
          if (i < x && (bo & 8)) continue;
          for (int s = 0; s < 4; s ++)
            Inc( dp[nxt][bo | msk][s | ss], dp[cur][bo][s] );
        }
        swap(cur, nxt);
      }
    return (0ll + dp[cur][15][0] + dp[cur][15][1] + dp[cur][15][2]) % mod;
  }
public:
  inline int countPatterns(int X, int Y, int n, int m) {
    nn = n; mm = m;
    long long ans = 1;
    for (int i = 1; i <= X; i ++)
      for (int j = 1; j <= Y; j ++)
        ( ans += 1ll * calc(i, j) * (X - i + 1) % mod * (Y - j + 1) % mod ) %= mod;
    return (int)ans;
  }
};
