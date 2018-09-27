#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;
 
typedef long long LL;
const int N = 210;
const int mod = 1e9 + 7;
 
class TrickyInequality {
private:
  int n, m, c[N][N], f[N][N], stir1[N], stir2[N];
  inline LL Pow(int x, int exp = mod - 2) {
    LL res = 1;
    for (; exp; exp >>= 1, x = 1ll * x * x % mod)
      if (exp & 1) res = res * x % mod;
    return res;
  }
  inline LL C(int x, int y) {
    if (m >= N) {
      if (y >= N) y = x - y;
      return c[m - x][y];
    }
    else return c[x][y];
  }
  inline void Init() {
    if (m >= N) {
      c[N - 1][0] = 1;
      for (int j = 1; j < N; j ++)
        c[N - 1][j] = 1ll * c[N - 1][j - 1] * Pow(j) % mod * ( m - (N - 1) - (j - 1) ) % mod;
      for (int i = N - 2; ~ i; i --) {
        c[i][0] = 1;
        for (int j = 1; j < N; j ++)
          c[i][j] = ( c[i + 1][j] + c[i + 1][j - 1] ) % mod;
      }
    } else {
      for (int i = 0; i < N; i ++) {
        c[i][0] = 1;
        for (int j = 1; j <= i; j ++)
          c[i][j] = ( c[i - 1][j - 1] + c[i - 1][j] ) % mod;
      }
    }
    f[0][0] = 1;
    for (int i = 2; i < N; i ++)
      for (int j = 1; j <= i; j ++)
        f[i][j] = (1ll * (i - 1) * f[i - 2][j - 1] + 1ll * j * f[i - 1][j]) % mod;
    for (int i = n; i <= m; i ++) {
      int &res = stir2[i - n];
      for (int j = 0; j <= i - n; j ++)
        res = ( res + f[i - n + j][j] * C(i, i - n + j) ) % mod;
    }
    memset(f, 0, sizeof f);
    f[0][0] = 1;
    for (int i = 2; i < N; i ++)
      for (int j = 1; j <= i; j ++)
        f[i][j] = ( 1ll * (i - 1) * ( f[i - 2][j - 1] + f[i - 1][j] ) ) % mod;
    for (int i = n; i <= m; i ++) {
      int &res = stir1[i - n];
      for (int j = 0; j <= m - i; j ++)
        res = ( res + f[m - i + j][j] * C(m, m - i + j) ) % mod;
    }
  }
public:
  inline int countSolutions(LL s, int t, int _n, int _m) {
    n = _n; m = _m; Init(); s %= mod;
    LL res = 0, powt = Pow(t, n);
    for (int i = n; i <= m; i ++) {
      LL cur = powt;
      for (int j = i; j <= m; j ++) {
        if ((i + j) & 1) res += mod - stir2[i - n] * C(j, i) % mod * stir1[j - n] % mod * cur % mod;
        else res += stir2[i - n] * C(j, i) % mod * stir1[j - n] % mod * cur % mod;
        if (res >= mod) res -= mod;
        (cur *= s) %= mod;
      }
      (powt *= t) %= mod;
    }
    for (int i = m; i > n; i --) res = res * Pow(i) % mod;
    if ((n + m) & 1) res = mod - res;
    return res;
  }
};
