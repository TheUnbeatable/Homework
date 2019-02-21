#include <bits/stdc++.h>
using namespace std;

const int N = 1e6 + 50;

int n;
double f;
char s[N];
pair <double, int> a[N];

int main() {
  freopen("real.in", "r", stdin);
  freopen("real.out", "w", stdout);
  scanf("%lf", &f);
  scanf("%s", s + 1);
  n = strlen(s + 1);
  for (int i = 1, si = 0; i <= n; i ++) {
    si += s[i] - '0';
    a[i] = make_pair(f * i - si, i);
  }
  a[0] = make_pair(0, 0);
  sort(a, a + n + 1);
  double ans = 1e18;
  int l = 0;
  for (int i = 0; i < n; i ++) {
    double cur = fabs( (a[i].first - a[i + 1].first)
                       / (a[i].second - a[i + 1].second) );
    if (fabs(ans - cur) < 1e-9)
      l = min(l, min(a[i].second, a[i + 1].second));
    else if (ans > cur) {
      ans = cur;
      l = min(a[i].second, a[i + 1].second);
    }
  }
  printf("%d\n", l);
  return 0;
}
