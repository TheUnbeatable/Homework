#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

int main() {
  int n, d, x;
  scanf("%d%d%d", &n, &d, &x);
  long double dx = x, s = d, ans = 0;
  for (int i = 2 * n; i; i -= 2) {
    ans += (i - 1) * dx / 2 + s;
    s = (s * 2 + dx * 5 + i * s) / i;
    dx = dx * (4 + i) / i;
  }
  printf("%.10Lf\n", ans);
  return 0;
}
