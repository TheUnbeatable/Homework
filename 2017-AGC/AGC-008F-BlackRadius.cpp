#include <cstdio>
#include <iostream>
#define travel(x, y, i) for (int i = fir[x], y = e[i].to; i; i = e[i].nxt, y = e[i].to)
using namespace std;

const int N = 2e5 + 50;

struct edge {
  int nxt, to;
} e[N << 1];
int fir[N], cnt = 0;
int n, Max[N], high[N], sz[N], f[N], up[N];
char s[N];

inline void addedge(int x, int y) {
  e[++ cnt] = (edge) { fir[x], y }; fir[x] = cnt;
}

inline void Dfs(int x, int fa) {
  f[x] = fa;
  sz[x] = s[x] == '1';
  travel(x, y, i)
    if (y != fa) {
      Dfs(y, x);
      Max[x] = max(Max[x], Max[y] + 1);
      sz[x] += sz[y];
    }
}

inline void Dfshigh(int x, int fa, int lo) {
  int mx = ++ lo, sb = 0;
  travel(x, y, i)
    if (y != fa) {
      if (mx < Max[y] + 1) {
        sb = mx; mx = Max[y] + 1;
      }
      else sb = max(sb, Max[y] + 1);
    }
  high[x] = min(mx - 1, sb + 1);
  travel(x, y, i)
    if (y != fa) Dfshigh(y, x, max(lo, Max[y] + 1 != mx ? mx : sb));
  up[x] = lo;
}

int main() {
  scanf("%d", &n);
  for (int i = 1, x, y; i < n; i ++) {
    scanf("%d%d", &x, &y);
    addedge(x, y); addedge(y, x);
  }
  scanf("%s", s + 1);
  Dfs(1, 0);
  Dfshigh(1, 0, -1);
  long long ans = 1;
  for (int i = 1, low; i <= n; i ++) {
    low = 1e9;
    travel(i, v, j)
      if (v == f[i]) {
        if (sz[1] - sz[i]) low = min(low, up[i]);
      }
      else if (sz[v]) low = min(low, Max[v] + 1);
    if (s[i] == '1') low = 0;
    ans += max(0, high[i] - low + 1);
  }
  printf("%lld\n", ans);
  return 0;
}
