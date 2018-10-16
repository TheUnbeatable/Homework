#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

typedef long long LL;
const int N = 105;
const int mod = 1e9 + 7;

namespace MathCal {
  LL fac[N], ifac[N];
  inline LL Pow(LL x, LL exp = mod - 2) {
    LL res = 1;
    for (; exp; exp >>= 1, x = x * x % mod)
      if (exp & 1) res = res * x % mod;
    return res;
  }
  inline void Init() {
    for (int i = fac[0] = 1; i < N; i ++) fac[i] = fac[i - 1] * i % mod;
    ifac[N - 1] = Pow(fac[N - 1], mod - 2);
    for (int i = N - 1; i; i --) ifac[i - 1] = ifac[i] * i % mod;
  }
  inline LL C(int x, int y) {
    return (y > x || x < 0 || y < 0) ? (0) : (fac[x] * ifac[y] % mod * ifac[x - y] % mod);
  }
}
using namespace MathCal;

struct node {
  int rem, len;
  node() {}
  node(string s) {
    len = s.length(); rem = 0;
    for (int i = 0; i < len; i ++)
      rem = (rem * 10ll + s[i] - '0') % mod;
  }
};

class AnyNumber {
private:
  node s[N];
  int n, m, a[N];
  int dp[N][N], f[N][N], pw[N], buc[N];
  template <typename T1, typename T2>
  inline void Inc(T1 &a, T2 b) {
    if ((a += b) >= mod) a -= mod;
  }
public:
  inline void calc() {
    memset(dp, 0, sizeof dp);
    dp[0][0] = 1;
    for (int i = 1; i < m; i ++)
      for (int j = 0; j <= n; j ++)
        for (int k = 0; k < a[i] && k <= j; k ++)
          Inc(dp[i][j], dp[i - 1][j - k] * C(j, k) % mod * C(a[i], k) % mod * fac[k] % mod);
  }
  inline int findExpectation(vector <string> cards, vector <int> blank) {
    MathCal :: Init();
    for (int i = pw[0] = 1; i < N; i ++) pw[i] = pw[i - 1] * 10ll % mod;
    memset(f, 0, sizeof f);
    n = cards.size();
    for (int i = 1; i <= n; i ++) s[i] = node(cards[i - 1]);
    m = blank.size();
    int tot = 0;
    for (int i = 1; i <= m; i ++)
      a[i] = blank[i - 1], tot += a[i];
    for (int i = 1; i <= m; i ++) {
      swap(a[i], a[m]); calc();
      swap(a[i], a[m]);
      for (int j = a[i]; j <= n && j <= tot; j ++)
        f[j][i] = dp[m - 1][j - a[i]] * ifac[tot] % mod * fac[tot - j] % mod;
    }
    LL ans = 0;
    for (int d = 1; d <= n; d ++) {
      memset(buc, 0, sizeof buc);
      buc[0] = 1;
      for (int i = 1; i <= n; i ++) {
        if (i >= d) {
          for (int j = 1; j <= m; j ++)
            for (int k = 0; k < a[j]; k ++) {
              if (a[j] - k - 1 > 0 && i != d)
                Inc(ans, 1ll * f[i][j] * s[d].rem % mod * buc[k] % mod
                    * fac[k] % mod * fac[a[j] - k - 1] % mod * C(i - k - 2, a[j] - k - 2) % mod);
              if (i > d && k)
                Inc(ans, 1ll * f[i][j] * s[d].rem % mod * buc[k - 1] % mod * pw[s[i].len] % mod
                    * fac[k] % mod * fac[a[j] - k - 1] % mod * C(i - k - 1, a[j] - k - 1) % mod);
              if (i == d)
                Inc(ans, 1ll * f[i][j] * s[d].rem % mod * buc[k] % mod
                    * fac[k] % mod * fac[a[j] - k - 1] % mod * C(i - k - 1, a[j] - k - 1) % mod);
            }
        }
        if (i != d) {
          LL tmp = pw[s[i].len];
          for (int j = n; j; j --) Inc(buc[j], buc[j - 1] * tmp % mod);
        }
      }
    }
    return (int) ans;
  }
};
