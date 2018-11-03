#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 550;

class RedPaint {
private:
  double f[2][N][N];
public:
  inline double expectedCells(int n) {
    if (n <= 1) return n + 1;
    int cur = 0, nxt = 1;
    memset(f[nxt], 0, sizeof f[nxt]);
    for (int i = 2; i <= n + 1; i ++)
      for (int j = 1; j <= i; j ++)
        f[nxt][i][j] = i;
    for (int i = n; i >= 1; i --) {
      for (int j = 1; j <= i; j ++) {
        memset(f[cur][j], 0, sizeof f[cur][j]);
        for (int k = 1; k <= j; k ++) {
          f[cur][j][k] = (f[nxt][j + (k == 1)][k  - 1 + (k == 1)]
                          + f[nxt][j + (k == j)][k + 1]) / 2;
        }
      }
      swap(cur, nxt);
    }
    return f[nxt][1][1];
  }
};
