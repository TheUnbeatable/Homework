#include <cstdio>
#include <iostream>
#include <cstring>
using namespace std;

typedef long long LL;
const int N = 1e5 + 50;
const int incol[] = { 1, 2, 0 };
const int outcol[] = { 2, 0, 1 };

struct edge {
  int nxt, to;
} e[N << 1];
int fir[N], cnt = 0;
int n, m, col[N], tms[4], ce;
bool bad;

inline void addedge(int x, int y) {
  e[++ cnt] = (edge) { fir[x], y }; fir[x] = cnt;
}

inline void Dfs(int x) {
  int exp;
  tms[col[x]] ++;
  for (int i = fir[x]; i; i = e[i].nxt) {
    ce ++;
    if (i & 1) exp = outcol[col[x]];
    else exp = incol[col[x]];
    if (~ col[e[i].to]) {
      if (exp != col[e[i].to]) bad = 1;
    }
    else {
      col[e[i].to] = exp; Dfs(e[i].to);
    }
  }
}

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 1, x, y; i <= m; i ++) {
    scanf("%d%d", &x, &y);
    addedge(x, y); addedge(y, x);
  }
  memset(col, -1, sizeof col);
  LL ans = 0;
  for (int i = 1; i <= n; i ++)
    if (col[i] == -1) {
      ce = 0;
      tms[0] = tms[1] = tms[2] = 0;
      bad = 0; col[i] = 0; Dfs(i);
      if (bad) {
        int sum = tms[0] + tms[1] + tms[2];
        ans += (LL) sum * sum;
      }
      else if (tms[0] && tms[1] && tms[2])
        ans += (LL) tms[0] * tms[1] + (LL) tms[0] * tms[2] + (LL) tms[1] * tms[2];
      else ans += ce >> 1;
    }
  printf("%lld\n", ans);
  return 0;
}

