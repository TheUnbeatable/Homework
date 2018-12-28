#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
const int N = 1e6 + 1e5;
const int M = 53;
const int mod = 1e9 + 7;
const LL sqr = 6ll * mod * mod;
const LL n = 1e12;
const int m = 50;

LL inv[M], D[M], co[M][M];
int rec[N << 1][M];
unordered_set <LL> done;

inline LL Pow(LL x, LL exp) {
  LL res = 1;
  for (; exp; exp >>= 1, x = x * x % mod)
    if (exp & 1) res = res * x % mod;
  return res;
}

inline LL calc(LL x, int exp) {
  if (!exp || x <= 0) return x;
  int pos = (x < N ? x : n / x + N + 1);
  if (rec[pos][exp]) return rec[pos][exp];
  x %= mod;
  LL res = 0, t = x;
  for (int i = 1; i <= exp + 1; i ++) {
    res += t * co[exp][i];
    res -= (res >= sqr ? sqr : 0);
    t = t * (x - i) % mod * inv[i + 1] % mod;
  }
  res %= mod;
  if (res < 0) res += mod;
  return rec[pos][exp] = res;
}

inline void Init() {
  for (int i = inv[0] = 1; i < M; i ++)
    inv[i] = Pow(i, mod - 2);
  for (int i = 1; i <= 50; i ++) {
    D[0] = 0;
    for (int j = 1; j <= i + 1; j ++) {
      D[j] = Pow(j, i);
      D[j] += D[j - 1];
      if (D[j] >= mod) D[j] -= mod;
    }
    for (int j = 1; j <= i + 1; j ++) {
      for (int k = 0; k <= i; k ++) {
        D[k] = D[k + 1] - D[k];
        if (D[k] < 0) D[k] += mod;
      }
      co[i][j] = D[0];
    }
  }
}

int f[N][M];
bitset <N> notp;

inline void sieve(int n) {
  static LL pw[M];
  for (int i = 1; i <= n; i ++)
    for (int j = 1; j <= m; j ++) f[i][j] = 1;
  for (int i = 2; i <= n; i ++)
    if (!notp[i])  {
      for (int j = pw[0] = 1; j <= m; j ++)
        pw[j] = pw[j - 1] * i % mod;
      for (int j = 1; j <= m; j ++)
        pw[j] = mod + pw[j] * (1 - pw[j]) % mod;
      for (int j = i; j <= n; j += i) {
        notp[j] = 1;
        int *u = f[j];
        for (int k = 1; k <= m; k ++)
          u[k] = pw[k] * u[k] % mod;
      }
    }
}

LL ans = 0;

inline void solve() {
  for (LL i = 1; i * i * i <= n; i ++) {
    for (int j = i; ; j += i) {
      LL rng = n / i / j / j;
      if (!rng) break;
      if (done.count(i * j * j)) continue;
      done.insert(i * j * j);
      for (int k = 1; k <= m; k ++)
        ans = (ans + calc(rng, k) * f[j][k]) % mod;
    }
  }
}

int main() {
  done.rehash(N << 1);
  Init();
  sieve(sqrt(n) + 5);
  solve();
  printf("%lld\n", ans % mod);
  return 0;
}
