#include <bits/stdc++.h>
#define lb(x) ((x) & (- (x)))
using namespace std;

int n, a[1010], pre[1010];
bitset <1 << 13 | 8> f[1010];
int vis[1010][1 << 13 | 2], cur;
bool yes;

inline int maxbit(int x) {
  int ans = 0;
  if (x >= 256) x >>= 8, ans += 8;
  if (x >= 16) x >>= 4, ans += 4;
  if (x >= 4) x >>= 2, ans += 2;
  ans += (x >= 2);
  return ans;
}

inline void Dfs(int n, int l) {
  if (yes || !n) return (void)(yes = 1);
  int r = pre[n] - l;
  if (l < r) swap(l, r);
  if (vis[n][l] == cur) return;
  vis[n][l] = cur;
  if (l >= a[n]) {
    // put l
    if (maxbit(l - a[n]) != maxbit(r) || !maxbit(r)) {
      if (!r && l - a[n] < a[n] * 2) Dfs(n - 1, l - a[n]);
      else if (lb(l - a[n]) >= a[n] || l == a[n]) Dfs(n - 1, l - a[n]);
    }
  }
  if (r >= a[n])
    if (maxbit(r - a[n]) != maxbit(l) || !maxbit(l))
      if (lb(r - a[n]) >= a[n] || r == a[n]) Dfs(n - 1, l);
}

inline void solve() {
  scanf("%d", &n);
  int MIN = 1 << 13;
  for (int i = 1; i <= n; i ++) {
    scanf("%d", &a[i]);
    pre[i] = pre[i - 1] + a[i];
    MIN = min(MIN, a[i]);
  }
  for (int i = 1; i <= n; i ++)
    a[i] /= MIN, pre[i] /= MIN;
  if (lb(pre[n]) != pre[n]) return (void)puts("NO");
  cur ++;
  yes = 0;
  Dfs(n, pre[n]);
  Dfs(n, pre[n] / 2);
  puts(yes ? "YES" : "NO");
}

int main() {
  freopen("2048.in", "r", stdin);
  freopen("2048.out", "w", stdout);
  int T; scanf("%d", &T);
  while (T --) solve();
  return 0;
}
