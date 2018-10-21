#include <cstdio>
#include <iostream>
#define ri register int
using namespace std;
     
const int N = 2e5 + 50;
     
int n, v, m;
int lb[N], rb[N], ans[N];
int pre[N][18], nxt[N][18];
int a[N], f[1 << 18 | 5], g[1 << 18 | 5];

int main() {
  scanf("%d%d", &n, &v);
  int rec = v; v >>= 1;
  for (int i = 1; i <= n; i ++) scanf("%d", &a[i]);
  for (int t = v; t; t >>= 1) m ++;
  m ++;
  for (int j = 1; j < m; j ++)
    nxt[n + 1][j] = n + 1;
  lb[0] = 1; rb[n + 1] = n;
  for (ri i = 1; i <= n; i ++) {
    lb[i] = (a[i] - a[i - 1] > rec) ? i : lb[i - 1];
    for (ri j = 0; j < m; j ++)
      pre[i][j] = ((a[i] - a[i - 1]) > (v >> j)) ? i - 1 : pre[i - 1][j];
  }
  for (ri i = n; i; i --) {
    rb[i] = (a[i + 1] - a[i] > rec) ? i : rb[i + 1];
    for (ri j = 0; j < m; j ++)
      nxt[i][j] = ((a[i + 1] - a[i]) > (v >> j)) ? i + 1 : nxt[i + 1][j];
  }
  for (ri i = 0, l, r; i < (1 << m); i ++) {
    l = 1; r = n;
    for (ri j = 0; j < m; j ++)
      if ((i >> j) & 1) {
    	l = max(l, nxt[f[i ^ (1 << j)]][j]);
    	r = min(r, pre[g[i ^ (1 << j)]][j]);
      }
    f[i] = l; g[i] = r;
  }
  bool allok = 0;
  int U = (1 << m) - 1;
  for (ri i = 0, p; i < (1 << m); i ++) {
    p = rb[f[i]];
    if (g[U ^ i] <= p) ans[p] = 1;
    if (g[U ^ i] < f[i]) allok = 1;
  }
  for (int i = 1; i <= n; i ++)
    if (ans[rb[i]] || allok) puts("Possible");
    else puts("Impossible");
  return 0;
}
