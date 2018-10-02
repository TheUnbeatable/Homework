#include <cstdio>
#include <iostream>
#define rs register short
#define ri register int
using namespace std;

typedef long long LL;
const int N = 2001;
const int K = N << 2;
const int M = 2e5 + 5;
const LL mod = 1e9 + 7;

template <typename T> inline void read(T &x) {
  char ch; x = 0;
  while (!isdigit(ch = getchar()));
  do {x = (x << 1) + (x << 3) + ch - '0';} while (isdigit(ch = getchar()));
}

namespace MathCal {
  LL fac[K], inv[K];
  inline LL Co(int x, int y) {
    if (x < y) return 0;
    return fac[x] * inv[y] % mod * inv[x - y] % mod;
  }
  inline LL pow(LL x, LL exp) {
    LL ret = 1;
    for (; exp; exp >>= 1, x = x * x % mod)
      if (exp & 1) ret = ret * x % mod;
    return ret;
  }
  inline void pre() {
    for (int i = fac[0] = 1; i < K; i ++) fac[i] = fac[i - 1] * i % mod;
    inv[K - 1] = pow(fac[K - 1], mod - 2);
    for (int i = K - 1; i >= 1; i --) inv[i - 1] = inv[i] * i % mod;
  }
}
using namespace MathCal;

int dp[N << 1][N << 1];
int a[M], b[M], n;

inline void adj(int &x) {
  if (x >= mod) x -= mod;
}

int main() {
  int Maxx = 0, Maxy = 0;
  pre();
  read(n);
  for (ri i = 1; i <= n; i ++) {
    read(a[i]); read(b[i]);
    Maxx = max(Maxx, a[i]);
    Maxy = max(Maxy, b[i]);
    dp[N - a[i]][N - b[i]] ++;
  }
  int A = N - Maxx, B = N + Maxx, C = N - Maxy, D = N + Maxy;
  for (rs i = A; i <= B; i ++)
    for (rs j = C; j <= D; j ++) {
      dp[i][j] += dp[i - 1][j];
      adj(dp[i][j]);
      dp[i][j] += dp[i][j - 1];
      adj(dp[i][j]);
    }
  LL ans = 0;
  for (ri i = 1; i <= n; i ++) {
    ans += dp[a[i] + N][b[i] + N] - Co(a[i] + a[i] + b[i] + b[i], a[i] + a[i]);
    if (ans < 0) ans += mod;
    if (ans >= mod) ans -= mod;
  }
  printf("%lld\n", ans * pow(2LL, mod - 2) % mod);
  return 0;
}
