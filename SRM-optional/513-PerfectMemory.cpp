#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <ctime>
#include <cmath>
using namespace std;

const int N = 1300;

class PerfectMemory {
private :
  double dp[N][N];
public :
  inline double getExpectation(int N, int M) {
    int n = N * M / 2;
    dp[n][0] = 0;
    for (int i = n - 1; ~ i; i --)
      for (int j = n - i; ~ j; j --) {
        int k = n - i - j;
        // i: count of solved pairs of symbols
        // j: count of opened symbols
        // k: count of unopened symbols
        double &c = dp[i][j] = 0;
        int m = k * 2 + j;
        // opened
        if (j) c += (dp[i + 1][j - 1] + 1) * j / m;
        // unopend + same_unopened
        if (m > 1 && i + j + 1 <= n)
          c += (dp[i + 1][j] + 1) * (k * 2) / m / (m - 1);
        // unopend + opened
        if (m > 1 && i + j + 1 <= n)
          c += (dp[i + 1][j] + 2) * (k * 2) / m * j / (m - 1);
        // unopend + another_unopened
        if (k > 1 && m > 1 && i + j + 2 <= n)
          c += (dp[i][j + 2] + 1) * (k * 2) / m * (k * 2 - 2) / (m - 1);
      }
    return dp[0][0];
  }
};
