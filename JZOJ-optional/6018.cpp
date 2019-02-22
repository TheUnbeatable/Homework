#include <bits/stdc++.h>
using namespace std;

const int N = 1e7 + 50;

int n, k;
char s[N];
int fix[N];
bitset <N> vis;

int main() {
  freopen("modulo.in", "r", stdin);
  freopen("modulo.out", "w", stdout);
  scanf("%d", &k);
  scanf("%s", s + 1);
  n = strlen(s + 1);
  s[0] = '0';
  int ans = 0;
  for (int p = k - 1; p; p --) {
    for (int i = 1; i <= n; i ++)
      fix[i] = fix[i - 1] + (s[i - 1] - s[i] + k) % k - (vis[i] ? k : 0);
    if (p == k - 1) ans = fix[n];
    int sufmin = 1e9;
    for (int i = n; i; i --) {
      sufmin = min(sufmin, fix[i]);
      if (sufmin < k) break;
      if ((s[i - 1] - s[i] + k) % k == p) {
        ans -= p; vis[i] = 1; sufmin -= k;
      }
    }
  }
  printf("%d\n", ans);
  return 0;
}
