#include <bits/stdc++.h>
using namespace std;

const int N = 110;
const int mod = 1e4 + 7;

int f[N][N], C[N][N], fac[N];
int T, n, m, fx[N], fy[N];
bool vis[N], vx[N], vy[N];

inline int calc(int msk) {
  // precheck
  memset(vx, 0, sizeof vx);
  memset(vy, 0, sizeof vy);
  for (int i = 0; i < m; i ++)
    if ((msk >> i) & 1) {
      if (vx[fx[i]] || vy[fy[i]]) return 0;
      vx[fx[i]] = vy[fy[i]] = 1;
    }
  long long ans = 0, local;
  int rem = n - __builtin_popcount(msk);
  int s = 1, occ = 0, ns = 1;
  // unbounded
  ans = fac[rem];
  // diagonal_1 empty
  local = 0;
  memset(vis, 0, sizeof vis);
  for (int i = 0; i < m; i ++)
    if ((msk >> i) & 1) {
      if (fx[i] == fy[i]) s = 0;
      vis[fx[i]] = vis[fy[i]] = 1;
    }
  ns &= s;
  for (int i = 1; i <= n; i ++) occ += vis[i];
  for (int i = 0; i <= n - occ; i ++, s = - s)
    local += C[n - occ][i] * fac[rem - i] * s;
  ans -= local;
  // diagonal_2 empty
  local = 0;
  s = 1; occ = 0;
  memset(vis, 0, sizeof vis);
  for (int i = 0; i < m; i ++)
    if ((msk >> i) & 1) {
      if (fx[i] == n - fy[i] + 1) s = 0;
      vis[fx[i]] = vis[n - fy[i] + 1] = 1;
    }
  ns &= s;
  for (int i = 1; i <= n; i ++) occ += vis[i];
  for (int i = 0; i <= n - occ; i ++, s = - s)
    local += C[n - occ][i] * fac[rem - i] * s;
  ans -= local;
  // both diagonals empty
  if (!ns) return (ans % mod + mod) % mod;
  local = 0;
  static int dp[N];
  memset(dp, 0, sizeof dp);
  memset(vx, 0, sizeof vx);
  memset(vy, 0, sizeof vy);
  dp[0] = 1;
  for (int i = 0; i < m; i ++)
    if ((msk >> i) & 1) vx[fx[i]] = vy[fy[i]] = 1;
  for (int i = 1; i <= n / 2; i ++) {
    int xi = vx[i] + vx[n + 1 - i];
    int yi = vy[i] + vy[n + 1 - i];
    if (xi == 2 || yi == 2) continue;
    if (xi && yi) {
      for (int j = i * 2; j; j --) {
        dp[j] += dp[j - 1];
        dp[j] -= (dp[j] >= mod ? mod : 0);
      }
    } else if (xi || yi) {
      for (int j = i * 2; j; j --) {
        dp[j] += dp[j - 1] << 1;
        dp[j] -= (dp[j] >= mod ? mod : 0);
        dp[j] -= (dp[j] >= mod ? mod : 0);
      }
    } else {
      for (int j = i * 2; j; j --) {
        if (j > 1) dp[j] += dp[j - 2] << 1;
        (dp[j] += dp[j - 1] << 2) %= mod;
      }
    }
  }
  if ( (n & 1) && !vx[n / 2 + 1] && !vy[n / 2 + 1] ) {
    for (int i = n; i; i --) {
      dp[i] += dp[i - 1];
      dp[i] -= (dp[i] >= mod ? mod : 0);
    }
  }
  s = 1;
  for (int i = 0; i <= rem; i ++, s = - s)
    local += dp[i] * fac[rem - i] * s;
  ans += local;
  return (ans % mod + mod) % mod;
}

inline void solve() {
  scanf("%d%d", &n, &m);
  for (int i = 0; i < m; i ++) {
    scanf("%d%d", &fx[i], &fy[i]);
    fx[i] ++; fy[i] ++;
  }
  int ans = 0;
  for (int i = 0; i < (1 << m); i ++)
    ans += ( ( __builtin_popcount(i) & 1 ) ? -1 : 1 ) * calc(i);
  printf("%d\n", (ans % mod + mod) % mod);
}

int main() {
  freopen("rook.in", "r", stdin);
  freopen("rook.out", "w", stdout);
  for (int i = 0; i < N; i ++) {
    C[i][0] = 1;
    for (int j = 1; j <= i; j ++)
      C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % mod;
  }
  for (int i = fac[0] = 1; i < N; i ++)
    fac[i] = fac[i - 1] * i % mod;
  scanf("%d", &T);
  for (; T; T --) solve();
  return 0;
}
