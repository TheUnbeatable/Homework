#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;

typedef long long LL;
const int N = 1e5 + 5;

LL a[N], tms[N], ans[N];

int main() {
  LL x;
  int n, q, top = 0;
  scanf("%d%d", &n, &q);
  a[++ top] = n;
  for (int i = 1; i <= q; i ++) {
    scanf("%lld", &x);
    while (a[top] >= x && top > 0) top --;
    a[++ top] = x;
  }
  tms[top] = 1;
  for (int i = top; i >= 1; i --) {
    LL k = a[i];
    while (k > a[1]) {
      int p = lower_bound(a + 1, a + top + 1, k) - a - 1;
      tms[p] += k / a[p] * tms[i];
      k %= a[p];
    }
    ans[k] += tms[i];
  }
  for (int i = n; i >= 1; i --) ans[i] += ans[i + 1];
  for (int i = 1; i <= n; i ++) printf("%lld\n", ans[i]);
  return 0;
}
