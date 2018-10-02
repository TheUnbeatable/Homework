#include <cstdio>
#include <iostream>
using namespace std;

typedef long long LL;
const int N = 1e5 + 5;

int a[N];
LL dif[N << 1], ddif[N << 1], ans = 0;

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; i ++) scanf("%d", &a[i]);
  for (int i = 2, s; i <= n; i ++) {
    s = (a[i] + m - a[i - 1]) % m;
    dif[a[i] + m + 1] --;
    dif[a[i] + m - s + 2] ++;
    ddif[a[i] + m + 1] -= s - 1;
    ans += s;
  }
  for (int i = 1; i <= (m << 1); i ++) dif[i] += dif[i - 1];
  for (int i = 1; i <= (m << 1); i ++) dif[i] += dif[i - 1] + ddif[i];
  LL sub = 0;
  for (int i = 1; i <= m; i ++) sub = max(sub, dif[i] + dif[i + m]);
  printf("%lld\n", ans - sub);
  return 0;
}
