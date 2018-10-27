#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 210;
const int mod = 1e9 + 7;
const int m = 200;

int dp[N][N][N], C[N][N];

inline long long Pow(long long x, int exp = mod - 2) {
  long long res = 1;
  for (; exp; exp >>= 1) {
    if (exp & 1) res = res * x % mod;
    x = x * x % mod;
  }
  return res;
}

inline void Inc(int &a, int b) {
  if ((a += b) >= mod) a -= mod;
}

int main() {
  dp[m][0][0] = 1;
  for (int i = 0; i < N; i ++) {
    C[i][0] = 1;
    for (int j = 1; j <= i; j ++)
      C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % mod;
  }
  for (int i = m; ~ i; i --)
    for (int j = m - i; ~ j; j --)
      for (int k = m - i - j; ~ k; k --) {
        long long tmp = dp[i][j][k];
        if (!tmp) continue;
        // if (tmp)
        //   cerr << i << " " << j << " " << k << ": " << tmp << endl;
        for (int a = min(i, 4); ~ a; a --)
          for (int b = min(j, 4 - a); ~ b; b --)
            if (4 - a - b <= k)
              Inc( dp[i - a][j - b + a][k - (4 - a - b) + b],
                   tmp * C[i][a] % mod * C[j][b] % mod * C[k][4 - a - b] % mod * 24 % mod );
      }
  long long f = 1;
  for (int i = 1; i <= m; i ++) f = f * i % mod;
  printf("%lld\n", Pow(f) * dp[0][0][0] % mod);
  return 0;
}
