#include <bits/stdc++.h>
using namespace std;

const int N = 12;
const double pi = acos(-1);

int r[N], id[N], n, top, a[N];

inline double solve() {
  double L, R = 1e6, mid;
  for (int i = 1; i <= top; i ++) {
    a[i] = r[id[i]] * r[id[i + 1]];
    R = min(R, (double) a[i]);
  }
  L = - R;
  for (int T = 1; T <= 60; T ++) {
    mid = (L + R) / 2;
    double sum = 0;
    for (int i = 1; i <= top; i ++)
      sum += acos(mid / a[i]);
    if (sum < 2 * pi) R = mid;
    else L = mid;
  }
  double sum = 0;
  for (int i = 1; i <= top; i ++)
    sum += acos(mid / a[i]);
  if (fabs(sum - 2 * pi) > 1e-7) return 0;
  double ans = 0;
  for (int i = 1; i <= top; i ++)
    ans += sin(acos(L / a[i])) * a[i];
  return ans / 2;
}

int main() {
  freopen("yja.in", "r", stdin);
  freopen("yja.out", "w", stdout);
  scanf("%d", &n);
  for (int i = 1; i <= n; i ++) scanf("%d", &r[i]);
  double ans = 0;
  for (int i = 1; i < (1 << n); i ++) {
    top = 0;
    for (int j = 0; j < n; j ++)
      if ((i >> j) & 1) id[++ top] = j + 1;
    if (top <= 2) continue;
    id[top + 1] = id[1];
    do {
      ans = max(ans, solve());
    } while (next_permutation(id + 2, id + top + 1));
  }
  printf("%.7lf\n", ans);
  return 0;
}
