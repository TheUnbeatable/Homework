#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
const int N = 60;
const int mod = 998244353;
const LL sqr = 6ll * mod * mod;

int n, k, q, T;

struct Mat {
  int a[N][N];
  Mat() { memset(a, 0, sizeof a); }
};

struct Nut {
  vector <LL> a[N][N];
  inline void resize() {
    for (int i = 1; i <= n; i ++)
      for (int j = 1; j <= n; j ++) a[i][j].resize(T + 1);
  }
};

inline Mat Mul(const Mat &p, const Mat &q) {
  static Mat res;
  for (int i = 1; i <= n; i ++)
    for (int j = 1; j <= n; j ++) {
      LL t = 0;
      for (int k = 1; k <= n; k ++) {
        t += (LL)p.a[i][k] * q.a[k][j];
        t -= (t >= sqr ? sqr : 0);
      }
      res.a[i][j] = t % mod;
    }
  return res;
}

Mat power[40];
Nut nut[40];
LL inv[N], fac[N];

inline LL Pow(LL x, LL exp = mod - 2) {
  LL res = 1;
  for (; exp; exp >>= 1, x = x * x % mod)
    if (exp & 1) res = res * x % mod;
  return res;
}

inline Nut calc(const Nut &x, int exp) {
  static LL C[N];
  Mat &G = power[exp];
  Nut y = nut[exp];
  int w = 1 << exp;
  for (int i = C[0] = 1; i <= T; i ++)
    C[i] = C[i - 1] * (w - i + 1) % mod;
  for (int i = 0; i <= T; i ++)
    C[i] = C[i] * inv[i] % mod;
  for (int i = 1; i <= n; i ++)
    for (int j = 1; j <= n; j ++) {
      const vector <LL> &X = x.a[i][j];
      for (int p = 0; p <= T; p ++) {
        LL tmp = 0;
        for (int q = 0; q <= p; q ++) {
          tmp += X[q] * C[p - q];
          tmp -= (tmp >= sqr ? sqr : 0);
        }
        tmp %= mod;
        for (int k = 1; k <= n; k ++) {
          LL &u = y.a[k][j][p];
          u += G.a[k][i] * tmp;
          u -= (u >= sqr ? sqr : 0);
        }
      }
    }
  for (int i = 1; i <= n; i ++)
    for (int j = 1; j <= n; j ++)
      for (int k = 0; k <= T; k ++) y.a[i][j][k] %= mod;
  return y;
}

LL S[N][N];

inline void fileIO() {
  freopen("road.in", "r", stdin);
  freopen("road.out", "w", stdout);
}

int main() {
  fileIO();
  Mat &G = power[0];
  scanf("%d%d%d%d", &n, &k, &q, &T);
  for (int i = 1; i <= n; i ++)
    for (int j = 1; j <= n; j ++)
      scanf("%d", &G.a[i][j]);
  for (int i = 1; i <= 30; i ++)
    power[i] = Mul(power[i - 1], power[i - 1]);
  for (int i = fac[0] = 1; i <= T; i ++)
    fac[i] = fac[i - 1] * i % mod;
  for (int i = 0; i <= T; i ++) inv[i] = Pow(fac[i]);
  for (int i = 0; i <= 30; i ++) nut[i].resize();
  Nut &one = nut[0];
  for (int i = 1; i <= n; i ++) one.a[i][i][0] = 1;
  for (int i = 0; i < 30 && (2 << i) <= k; i ++) nut[i + 1] = calc(nut[i], i);
  Nut ans;
  ans.resize();
  for (int i = 0; i <= 30; i ++)
    if ((k >> i) & 1) ans = calc(ans, i);
  S[0][0] = 1;
  for (int i = 1; i <= T; i ++)
    for (int j = 1; j <= T; j ++)
      S[i][j] = ( S[i - 1][j - 1] + S[i - 1][j] * j ) % mod;
  for (int u, v; q; q --) {
    scanf("%d%d", &u, &v);
    LL res = 0;
    vector <LL> &w = ans.a[u][v];
    for (int i = 1; i <= T; i ++)
      res = ( res + S[T][i] * w[i] % mod * fac[i] ) % mod;
    printf("%lld\n", res);
  }
  return 0;
}
