#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

typedef long long LL;
const int N = 1e5 + 5;

int a[N], b[N], id[N], nxt[N][62];
LL tab[N];

int main() {
  int n, m;
  LL k;
  scanf("%d", &n);
  for (int i = 1; i <= n; i ++) scanf("%d", &a[i]);
  for (int i = n; i; i --) a[i] -= a[i - 1], id[i] = i;
  scanf("%d%lld", &m, &k);
  for (int i = 1, x; i <= m; i ++) {
    scanf("%d", &x);
    swap(id[x], id[x + 1]);
  }
  for (int i = 1; i <= n; i ++) nxt[id[i]][0] = i;
  tab[0] = 1;
  for (int i = 1; i < 62; i ++) {
    for (int j = 1; j <= n; j ++) nxt[j][i] = nxt[nxt[j][i - 1]][i - 1];
    tab[i] = tab[i - 1] << 1;
  }
  LL t;
  for (int i = 1, p; i <= n; i ++) {
    t = k;
    p = i;
    for (int j = 61; (~ j) && t; j --)
      if (tab[j] <= t) {
	t -= tab[j];
	p = nxt[p][j];
      }
    b[p] = a[i];
  }
  k = 0;
  for (int i = 1; i <= n; i ++) {
    k += b[i];
    printf("%lld.0\n", k);
  }
  return 0;
}
