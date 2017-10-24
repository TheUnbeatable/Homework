#include <cstdio>
#include <iostream>
using namespace std;

typedef long long LL;

const int N = 205;
const LL mod = 998244353LL;

LL ans, base[N];
bool done[N][N];
LL x[N], y[N];
int sta[N], top;

inline LL mul(int a, int b, int c) {
  return (x[b] - x[a]) * (y[c] - y[a]) - (x[c] - x[a]) * (y[b] - y[a]);
}

int main() {
  int n;
  scanf("%d", &n);
  ans = 1;
  base[0] = 1;
  for (int i = 1; i <= n; i ++) base[i] = base[i - 1] * 2LL % mod;
  ans = base[n];
  for (int i = 1; i <= n; i ++) scanf("%lld%lld", &x[i], &y[i]);
  ans = (ans + mod - n - 1) % mod;
  for (int i = 1; i <= n; i ++)
    for (int j = 1; j <= n; j ++)
      if (!done[i][j] && i != j) {
	top = 0;
	sta[++ top] = i;
	sta[++ top] = j;
	for (int k = 1; k <= n; k ++)
	  if (k != i && k != j && mul(i, j, k) == 0) sta[++ top] = k;
	ans = (mod + ans + top + 1 - base[top]) % mod;
	for (int k = 1; k <= top; k ++)
	  for (int l = 1; l < k; l ++) done[sta[k]][sta[l]] = done[sta[l]][sta[k]] = 1;
      }
  printf("%lld\n", ans);
  return 0;
}
