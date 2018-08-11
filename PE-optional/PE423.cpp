#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <bitset>
using namespace std;

typedef long long LL;
const int N = 5e7;
const LL mod = 1e9 + 7;
const LL INV4 = (mod + 1) / 4;

namespace MathCal {
  int fac[N + 5], inv[N + 5];
  inline int Pow(int x, int exp) {
    int res = 1;
    for (; exp; exp >>= 1, x = 1ll * x * x % mod)
      if (exp & 1) res = 1ll * res * x % mod;
    return res;
  }
  inline void Init() {
    for (int i = fac[0] = 1; i <= N; i ++)
      fac[i] = 1ll * fac[i - 1] * i % mod;
    inv[N] = Pow(fac[N], mod - 2);
    for (int i = N; i; i --)
      inv[i - 1] = 1ll * inv[i] * i % mod;
  }
  inline LL C(int x, int y) {
    return y > x ? 0 : 1ll * fac[x] * inv[y] % mod * inv[x - y] % mod;
  }
}
using MathCal :: C;

int pw[N + 10], pri[3100000], m;
bitset <N + 10> notp;

inline LL calcPoint(int x, int y) {
  if (x - y - 1 < 0) return 0;
  return C(x - 1, y) * pw[x - y - 1] % mod;
}

inline void Init() {
  MathCal :: Init();
  for (int i = pw[0] = 1; i < N; i ++)
    pw[i] = 5ll * pw[i - 1] % mod;
  pri[0] = 1;
  for (int i = 2; i < N; i ++) {
    if (!notp[i]) pri[++ m] = i;
    for (register int j = 1; j <= m; j ++) {
      int t = i * pri[j];
      if (t >= N) break;
      notp[t] = 1;
      if (i % pri[j] == 0) break;
    }
  }
}

inline void moveDown(int x, int y, int &v) {
  v += calcPoint(x + 1, y);
  if (v >= mod) v -= mod;
}

inline void moveRight(int x, int y, int &val) {
  int t = calcPoint(x, y + 1);
  val = ( ( t - ( val - calcPoint(x, y) ) ) * INV4 + t ) % mod;
  if (val < 0) val += mod;
}

int main() {
  Init();
  LL ans = 0;
  int up = 0;
  int down = (MathCal :: Pow(5, N) - 1) * INV4 % mod;
  for (int i = 0; i <= m; i ++) {
    ans += down - up;
    moveRight(N, i, down);
    moveRight(pri[i] - 1, i, up);
    for (int j = pri[i] - 1; j < pri[i + 1] - 1; j ++)
      moveDown(j, i + 1, up);
  }
  ans = (ans % mod + mod) % mod;
  printf("%lld\n", ans * 6 % mod);
  return 0;
}
