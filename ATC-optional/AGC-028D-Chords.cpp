#include <bits/stdc++.h>
using namespace std;

const int N = 610;
const int mod = 1e9 + 7;

int n, k, fix[N], f[N][N], mat[N];
long long g[N];

inline void calc(int l, int r) {
  for (int i = l; i <= r; i ++)
    if (mat[i]) if (mat[i] < l || mat[i] > r) return;
  long long ans = g[r - l + 1 - (fix[r] - fix[l - 1])];
  for (int i = l + 1; i < r; i ++)
    (ans -= f[l][i] * g[r - i - (fix[r] - fix[i])]) %= mod;
  f[l][r] = (ans % mod + mod) % mod;
}

int main() {
  scanf("%d%d", &n, &k);
  n *= 2;
  for (int i = 1, a, b; i <= k; i ++) {
    scanf("%d%d", &a, &b);
    fix[a] = fix[b] = 1;
    mat[a] = b; mat[b] = a;
  }
  g[0] = 1;
  for (int i = 1; i <= n; i ++) {
    fix[i] += fix[i - 1];
    g[i] = ( (i & 1) ? 0 : g[i - 2] * (i - 1) % mod );
  }
  long long ans = 0;
  for (int i = 2; i <= n; i += 2)
    for (int j = 1; i + j - 1 <= n; j ++) {
      calc(j, i + j - 1);
      int cont = 2 * k - (fix[i + j - 1] - fix[j - 1]);
      ans += f[j][i + j - 1] * g[n - i - cont] % mod;
    }
  printf("%lld\n", ans % mod);
  return 0;
}
