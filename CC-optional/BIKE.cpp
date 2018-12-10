#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
const int N = 24;
const int M = N * N;
const int G = 46;
const int mod = 1163962801;
const LL sqr = 4ll * mod * mod;

inline LL Pow(LL x, LL exp) {
  LL res = 1;
  for (; exp; exp >>= 1, x = x * x % mod)
    if (exp & 1) res = res * x % mod;
  return res;
}

int n;
int swp[N][N];

struct edge {
  int u, v, x, y;
} e[11000];

struct Mat {
  int a[N][N];
  inline void operator *= (const Mat &o) {
    for (int i = 1; i <= n; i ++)
      for (int j = 1; j <= n; j ++) {
        LL sum = 0;
        for (int k = 1; k + 1 <= n; k += 2) {
          sum += (LL) a[i][k] * o.a[k][j] + (LL) a[i][k + 1] * o.a[k + 1][j];
          if (sum >= sqr) sum -= sqr;
        }
        if (n & 1) sum += (LL) a[i][n] * o.a[n][j];
        swp[i][j] = sum % mod;
      }
    memcpy(a, swp, sizeof swp);
  }
} base, pwr;

int m, T;
int g[M], top, pn[M], pm[M];
int rec[N][N][N];

inline void solve(int x) {
  static int dft[N][N];
  LL iv = Pow(n * (n - 1), mod - 2);
  memcpy(dft, rec[x], sizeof dft);
  for (int ri = 0; ri < n; ri ++)
    for (int rj = 0; rj < n - 1; rj ++) {
      LL sum = 0;
      for (int i = 0; i < n; i ++)
        for (int j = 0; j < n - 1; j ++) {
          sum += (LL) dft[i][j] * pn[n - i * ri % n] % mod * pm[n - 1 - j * rj % (n - 1)];
          if (sum >= sqr) sum -= sqr;
        }
      sum %= mod;
      printf("%lld%c", sum * iv % mod, rj == n - 2 ? '\n' : ' ');
    }
}

int main() {
  scanf("%d%d%d", &n, &m, &T);
  for (int i = 1; i <= m; i ++) {
    scanf("%d%d%d%d", &e[i].u, &e[i].v, &e[i].x, &e[i].y);
    e[i].x %= n; e[i].y %= n - 1;
  }
  LL g = Pow(G, (mod - 1) / n);
  for (int i = pn[0] = 1; i <= n * n; i ++)
    pn[i] = pn[i - 1] * g % mod;
  g = Pow(G, (mod - 1) / (n - 1));
  for (int i = pm[0] = 1; i <= n * n; i ++)
    pm[i] = pm[i - 1] * g % mod;
  for (int ri = 0; ri < n; ri ++)
    for (int rj = 0; rj < n - 1; rj ++) {
      memset(base.a, 0, sizeof base.a);
      for (int i = 1; i <= m; i ++) {
        edge &E = e[i];
        base.a[E.u][E.v] = ( base.a[E.u][E.v]
                             + (LL) pn[ri * E.x] * pm[rj * E.y] ) % mod;
      }
      memset(pwr.a, 0, sizeof pwr.a);
      for (int i = 1; i <= n; i ++) pwr.a[i][i] = 1;
      for (int exp = T; exp; exp >>= 1) {
        if (exp & 1) pwr *= base;
        if (exp > 1) base *= base;
      }
      for (int i = 1; i <= n; i ++)
        rec[i][ri][rj] = pwr.a[i][i];
    }
  for (int i = 1; i <= n; i ++) solve(i);
  return 0;
}
