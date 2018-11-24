#include <bits/stdc++.h>
#define empty(s, p) (!((s >> (p)) & 1))
using namespace std;

int dp[1 << 16 | 1], cost[1 << 16 | 1][16];

class SixteenBricks {
private:
  inline void Init() {
    for (int i = 0; i < (1 << 16); i ++)
      for (int j = 0; j < 16; j ++)
        if (empty(i, j)) {
          int &k = cost[i][j] = 0;
          if (j & 3) {
            if (empty(i, j - 1)) k --;
            else k ++;
          }
          else k ++;
          if ((j & 3) != 3) {
            if (empty(i, j + 1)) k --;
            else k ++;
          }
          else k ++;
          if (j >= 4) {
            if (empty(i, j - 4)) k --;
            else k ++;
          }
          else k ++;
          if (j < 12) {
            if (empty(i, j + 4)) k --;
            else k ++;
          }
          else k ++;
        }
        else cost[i][j] = 100;
  }
  inline void chkmax(int &a, int b) { if (a < b) a = b; }
public:
  int maximumSurface(vector <int> height) {
    Init();
    sort(height.begin(), height.end());
    memset(dp, - 0x3f, sizeof dp);
    dp[0] = 0;
    for (int w = 0, h; w < 16; w ++) {
      h = height[w];
      for (int i = (1 << 16) - 1; ~ i; i --)
        for (int j = 0; j < 16; j ++)
          if (cost[i][j] != 100) chkmax(dp[i | (1 << j)], dp[i] + h * cost[i][j]);
    }
    return dp[(1 << 16) - 1] + 16;
  }
};
