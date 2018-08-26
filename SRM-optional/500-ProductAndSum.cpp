#include <cstdio>
#include <iostream>
#define ri register int
using namespace std;

typedef long long LL;
const LL mod = 500500573;
const int N = 2505;

namespace MathCal {
  LL fac[N], inv[N];
  inline LL pow(LL x, LL exp) {
    LL res = 1;
    for (; exp; exp >>= 1, x = x * x % mod)
      if (exp & 1) res = res * x % mod;
    return res;
  }
  inline void pre() {
    for (int i = fac[0] = 1; i < N; i ++) fac[i] = fac[i - 1] * i % mod;
    inv[N - 1] = pow(fac[N - 1], mod - 2);
    for (int i = N - 1; i; i --) inv[i - 1] = inv[i] * i % mod;
  }
  inline LL C(int x, int y) {
    if (y == 0 && x == 0) return 1LL;
    return y > x ? 0 : fac[x] * inv[y] % mod * inv[x - y] % mod;
  }
}
using namespace MathCal;

int tab[12];
LL val[N], a[12], b[12];

class ProductAndSum {
public :
  inline LL calc() {
    int w = 0;
    LL ans = 0, t;
    for (ri i = 1; i < 10; i ++) w += tab[i], a[i] = a[i - 1] * C(w, tab[i]) % mod;
    t = w --;
    for (ri i = 9; i >= 1; i --) {
      if (w < 0) b[i] = b[i + 1];
      else b[i] = b[i + 1] * C(w, tab[i]) % mod, w -= tab[i];
    }
    for (ri i = 1; i < 10; i ++)
      if (tab[i]) {
        w += tab[i];
        ans += a[i - 1] * b[i + 1] % mod * C(w, tab[i] - 1) % mod * val[t] % mod * i % mod;
        ans %= mod;
      }
    return ans;
  }
  inline int getSum(int p2, int p3, int p5, int p7, int S) {
    pre();
    for (int i = 1; i < N; i ++) val[i] = (val[i - 1] * 10 + 1) % mod;
    a[0] = 1; b[10] = 1;
    int d1, d2, d3, t = p2 * 2 + p3 * 3 + p5 * 5 + p7 * 7; LL ans = 0;
    tab[5] = p5; tab[7] = p7;
    for (ri d4 = 0; (d4 << 1) <= p2; d4 ++) {
      tab[4] = d4;
      for (ri d6 = 0; d6 <= p3; d6 ++) {
	if (d6 + d4 + d4 > p2) break;
	tab[6] = d6;
	for (ri d8 = 0; d6 + (d4 << 1) + d8 + (d8 << 1) <= p2; d8 ++) {
	  tab[8] = d8;
	  for (ri d9 = 0; (d9 << 1) + d6 <= p3; d9 ++) {
	    d1 = S - d6 - d9 * 3 - (d8 << 1) - t;
	    d2 = p2 - (d4 << 1) - d6 - d8 - (d8 << 1);
	    d3 = p3 - d6 - (d9 << 1);
	    if (d1 < 0 || d2 < 0 || d3 < 0) continue;
	    tab[9] = d9; tab[1] = d1; tab[2] = d2; tab[3] = d3;
	    (ans += calc()) %= mod;
	  }
	}
      }
    }
    return (int)ans;
  }
} solver;
