#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

LL n = (12017639147 + 3) / 2;
LL p[] = { 5, 11, 17, 23, 29, 41, 47 };
int m = sizeof(p) / sizeof(LL);
LL t = (3 - n % 3), ans = 0;


inline LL calc(LL n, int t) {
  return (n + 3 - t) / 3;
}

int main() {
  for (int i = 0; i < (1 << m); i ++) {
    LL tmp = 1;
    int tot = 0;
    for (int j = 0; j < m; j ++)
      if ((i >> j) & 1) {
        tot ++; tmp *= p[j];
      }
    if (tot & 1) ans -= calc(n / tmp, tmp % 3 == t ? 1 : 2);
    else ans += calc(n / tmp, tmp % 3 == t ? 1 : 2);
  }
  printf("%lld\n", ans);
  return 0;
}
