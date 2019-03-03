#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 50;

bool p[N];
long long a[N], b[N];
int n, s;

int main() {
  scanf("%d%d", &n, &s);
  for (int i = 1; i <= n; i ++)
    scanf("%lld%lld", &a[i], &b[i]);
  long long ans = 0;
  for (int pl = 1, pr = n; ;) {
    if (a[pl] > s) {
      ans += a[pr] - s;
      break;
    } else if (a[pr] < s) {
      ans += s - a[pl];
      break;
    } else {
      if (b[pl] >= b[pr]) {
        if (!p[pl]) ans += a[pr] - a[pl];
        p[pl] = 1; b[pl] += b[pr]; pr --;
      } else {
        if (!p[pr]) ans += a[pr] - a[pl];
        p[pr] = 1; b[pr] += b[pl]; pl ++;
      }
    }
  }
  printf("%lld\n", ans);
  return 0;
}
