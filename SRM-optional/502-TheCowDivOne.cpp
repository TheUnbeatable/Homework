#include <cstdio>
#include <iostream>
#include <map>
#include <algorithm>
using namespace std;

typedef long long LL;

class TheCowDivOne {
private :
  static const LL mod = 1e9 + 7;
  map <int, int> dp[1005];
  int n;
  inline LL rev(LL x) {
    LL exp = mod - 2, r = 1;
    for (; exp; exp >>= 1, x = x * x % mod)
      if (exp & 1) r = r * x % mod;
    return r;
  }
  inline LL Dfs(int p, int k) {
    if (k == 0) return 1;
    if (k == 1) return n / p;
    if (dp[k].count(p)) return dp[k][p];
    LL r = 0, sgn = 1;
    for (int i = 1; i <= k; i ++, sgn = - sgn) {
      r += sgn * Dfs(__gcd(i, p), k - i) * (n / p) % mod * __gcd(i, p) % mod;
      r %= mod; if (r < 0) r += mod;
    }
    r = r * rev(k) % mod;
    dp[k][p] = r;
    return r;
  }
public :
  inline int find(int N, int K) {
    n = N;
    return (int)Dfs(N, K);
  }
};
