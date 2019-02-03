#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
const int N = 10010;
const int mod = 1e9 + 9;

int a[N], b[N], n, m;
int C[100][100];

inline void init() {
  for (int i = 0; i < 100; i ++) {
    C[i][0] = 1;
    for (int j = 1; j <= i; j ++)
      C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % mod;
  }
}

inline LL Pow(LL x, int exp) {
  if (x < 0) x += mod;
  LL res = 1;
  for (; exp; exp >>= 1, x = x * x % mod)
    if (exp & 1) res = res * x % mod;
  return res;
}

int main() {
  init();
  scanf("%d", &n);
  for (int i = 1, x; i <= n; i ++) {
    scanf("%d", &x); a[x] ++;
  }
  scanf("%d", &m);
  for (int i = 1, x; i <= m; i ++) {
    scanf("%d", &x); b[x] ++;
  }
  LL ans = 1;
  n -= a[0];
  m -= b[0];
  for (int i = 1; i <= 10000; i ++) {
    if (!a[i] && !b[i]) continue;
    LL tmp = 0;
    for (int p = 0, sgn = 1; p <= a[i]; p ++, sgn = - sgn) {
      tmp = ( tmp + sgn * C[a[i]][p]
              * Pow( Pow(i + 1, n - p) - Pow(i, n - p), b[i] ) % mod
              * Pow(i, p * m) % mod
              * Pow( i + 1, (m - b[i]) * (a[i] - p) ) ) % mod;
    }
    ans = ans * tmp % mod;
    n -= a[i]; m -= b[i];
  }
  printf("%lld\n", (ans % mod + mod) % mod);
  return 0;
}

