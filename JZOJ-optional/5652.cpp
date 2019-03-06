#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 50;

int n, a[N];
char s[20];

inline void solve1() {
  // maximum goes last
  int gap = (n + 1) / 2, ans = 2e9;
  for (int i = 1, j = i + gap; j <= n; i ++, j ++)
    ans = min(ans, a[j] - a[i]);
  printf("%d\n", ans);
}

inline void solve2() {
  // minimum goes last
  int L = 1, R = 1e9, mid, ans = 1e9;
  while (L <= R) {
    mid = (L + R) >> 1;
    int tot = 0;
    for (int i = 1, j = 1; i <= n; i = j) {
      while (j <= n && a[j] - a[i] <= mid) j ++;
      tot ++;
    }
    if (tot <= (n + 1) / 2) R = mid - 1, ans = mid;
    else L = mid + 1;
  }
  printf("%d\n", ans);
}

inline void solve() {
  scanf("%s", s);
  for (int i = 1; i <= n; i ++) scanf("%d", &a[i]);
  bool who = s[0] == 's';
  if (who == (n & 1)) solve1();
  else solve2();
}

int main() {
  freopen("game.in", "r", stdin);
  freopen("game.out", "w", stdout);
  while (scanf("%d", &n) != EOF) solve();
  return 0;
}
