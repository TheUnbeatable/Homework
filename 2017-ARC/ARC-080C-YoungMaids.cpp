#include <cstdio>
#include <iostream>
#include <cstring>
#include <queue>
using namespace std;

const int N = 2e5 + 5;
const int B = 18;
const int INF = 1e9;

int a[N], pos[N], n;
bool vis[N];

struct Seg {
  int l, r, x;
  inline bool operator < (const Seg &o) const {
    return x > o.x;
  }
};
priority_queue <Seg> Q;

struct RMQ {
  int tab[B][N];
  RMQ() {
    memset(tab, 0, sizeof tab);
  }
  inline void Init() {
    for (int i = 1, d = 1; i < B; i ++, d <<= 1)
      for (int j = 1; j <= n - d; j ++)
	tab[i][j] = min(tab[i - 1][j], tab[i - 1][j + d]);
  }
  inline int Query(int l, int r) {
    int len = r - l + 1, d = 0, e = 1;
    for (; (e << 1) <= len; e <<= 1, d ++);
    return min(tab[d][l], tab[d][r - e + 1]);
  }
} qry[2];

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i ++) {
    scanf("%d", &a[i]);
    pos[a[i]] = i;
    qry[i & 1].tab[0][i] = a[i];
    qry[!(i & 1)].tab[0][i] = INF;
  }
  qry[0].Init();
  qry[1].Init();
  Q.push((Seg){1, n, qry[1].Query(1, n)});
  Seg c;
  int x, y, px, py;
  while (!Q.empty()) {
    c = Q.top(); Q.pop();
    x = c.x;
    px = pos[x];
    y = qry[!(c.l & 1)].Query(px + 1, c.r);
    py = pos[y];
    printf("%d %d ", x, y);
    if (c.l < px - 1) Q.push((Seg){c.l, px - 1, qry[c.l & 1].Query(c.l, px - 1)});
    if (px + 1 < py) Q.push((Seg){px + 1, py - 1, qry[(px + 1) & 1].Query(px + 1, py - 1)});
    if (py + 1 < c.r) Q.push((Seg){py + 1, c.r, qry[(py + 1) & 1].Query(py + 1, c.r)});
  }
  return 0;
}
