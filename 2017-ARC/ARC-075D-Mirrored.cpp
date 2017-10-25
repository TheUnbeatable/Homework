#include <cstdio>
#include <iostream>
#include <map>
using namespace std;

typedef long long LL;

map <LL, LL> rec[20][2];
LL pow10[20];

inline LL DP(int len, LL dif, bool pre) {
  if (len == 0) return (dif == 0);
  if (len == 1) return (dif == 0) * (10 - pre);
  if (rec[len][pre].count(dif)) return rec[len][pre][dif];
  LL ans = 0, t = pow10[len - 1] - 1, nxt;
    for (int i = pre; i <= 9; i ++)
      for (int j = 0; j <= 9; j ++) {
	nxt = dif - t * (j - i);
	if (nxt % 10 == 0) ans += DP(len - 2, nxt / 10, 0);
      }
  rec[len][pre][dif] = ans;
  return ans;
}

int main() {
  int D;
  pow10[0] = 1;
  for (int i = 1; i <= 18; i ++) pow10[i] = pow10[i - 1] * 10;
  scanf("%d", &D);
  LL ans = 0;
  for (int i = 1; i <= 18; i ++) ans += DP(i, (LL)D, 1);
  printf("%lld\n", ans);
  return 0;
}
