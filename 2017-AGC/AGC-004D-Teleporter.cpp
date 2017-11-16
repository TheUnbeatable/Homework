#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
#define rep(i, x, y) for (int i = (x); i <= (y); i ++)
#define travel(x, i) for (int i = fir[x]; i; i = e[i].nxt)
using namespace std;

const int N = 1e5 + 10;

struct edge {
  int nxt, to;
} e[N];
int fir[N], cnt = 0;
int n, k, ans = 0;
int mst[N], dep[N];

inline void addedge(int x, int y) {
  e[++ cnt] = (edge){fir[x], y};
  fir[x] = cnt;
}

inline void dfs(int x) {
  travel(x, i) {
    dep[e[i].to] = dep[x] + 1;
    dfs(e[i].to);
    mst[x] = max(mst[x], mst[e[i].to] + 1);
  }
  if (x != 1 && mst[x] == k - 1 && dep[x] != 1) ans ++, mst[x] = -1;
}

int main() {
  scanf("%d%d", &n, &k);
  int x;
  scanf("%d", &x);
  if (x != 1) ans = 1;
  rep(i, 2, n) {
    scanf("%d", &x);
    addedge(x, i);
  }
  dfs(1);
  printf("%d\n", ans);
  return 0;
}
