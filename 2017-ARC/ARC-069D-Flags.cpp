#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

const int N = 20005;

int n, x[N << 1], id[N << 1], rnk[N << 1], tab[N << 1], t;

namespace Graph {
#define mid ((L + R) >> 1)
#define no ID(L, R)
#define lc ID(L, mid)
#define rc ID(mid + 1, R)
#define travel(x, i) for (int i = fir[x]; i; i = e[i].nxt)
  struct edge {
    int nxt, to;
  } e[N * 100];
  int fir[N * 10], cnt;
  int dfn[N * 10], low[N * 10], clo;
  int bel[N * 10], sta[N * 10], top, cnt_bcc;
  bool vis[N * 10];
  
  inline int ID(int L, int R) {
    return ((L + R) | (L != R));
  }
  
  inline void add(int x, int y) {
    if (x == y) return;
    e[++ cnt] = (edge){fir[x], y};
    fir[x] = cnt;
  }
  
  inline void Build(int L, int R) {
    if (L == R) return;
    add(no, lc);
    Build(L, mid);
    add(no, rc);
    Build(mid + 1, R);
  }
  
  inline void Init() {
    memset(fir, 0, sizeof fir);
    cnt = 0;
    Build(0, t - 1);
  }
  
  inline void Add_edge(int L, int R, int x, int l, int r) {
    if (l > r) return;
    if (r < L || l > R) return;
    if (l <= L && R <= r) {
      add(x, no);
      return;
    }
    if (L == R) return;
    Add_edge(L, mid, x, l, r);
    Add_edge(mid + 1, R, x, l, r);
  }
  
  inline void dfs(int x) {
    vis[x] = 1;
    dfn[x] = low[x] = ++ clo;
    sta[++ top] = x;
    travel(x, i) {
      if (!dfn[e[i].to]) {
	dfs(e[i].to);
	low[x] = min(low[x], low[e[i].to]);
      }
      else if (vis[e[i].to]) low[x] = min(low[x], dfn[e[i].to]);
    }
    if (low[x] == dfn[x]) {
      int cur = -1;
      cnt_bcc ++;
      while (cur != x) {
	cur = sta[top --];
	bel[cur] = cnt_bcc;
      }
    }
    vis[x] = 0;
  }
  
  inline void Tarjan() {
    memset(bel, 0, sizeof bel);
    memset(dfn, 0, sizeof dfn);
    memset(vis, 0, sizeof vis);
    clo = top = cnt_bcc = 0;
    for (int i = 0; i <= ID(t - 1, t - 1); i ++)
      if (!dfn[i]) dfs(i);
  }
  
#undef mid
#undef no
#undef lc
#undef rc
}
using namespace Graph;

inline bool cmp(int a, int b) {
  return x[a] < x[b];
}

inline bool check(int ans) {
  Init();
  for (int i = 0, l, r; i < t; i ++) {
    l = lower_bound(tab, tab + t, x[i] - ans) - tab;
    r = upper_bound(tab, tab + t, x[i] + ans) - tab - 1;
    if (rnk[i] < l || rnk[i] > r)
      Add_edge(0, t - 1, ID(rnk[i ^ 1], rnk[i ^ 1]), l, r);
    else {
      Add_edge(0, t - 1, ID(rnk[i ^ 1], rnk[i ^ 1]), l, rnk[i] - 1);
      Add_edge(0, t - 1, ID(rnk[i ^ 1], rnk[i ^ 1]), rnk[i] + 1, r);
    }
  }
  Tarjan();
  for (int i = 0; i < t; i += 2)
    if (bel[ID(rnk[i], rnk[i])] == bel[ID(rnk[i ^ 1], rnk[i ^ 1])]) return false;
  return true;
}

int main() {
  scanf("%d", &n);
  t = n + n;
  for (int i = 0; i < t; i ++) {
    scanf("%d", &x[i]);
    id[i] = i;
  }
  sort(id, id + t, cmp);
  for (int i = 0; i < t; i ++) {
    rnk[id[i]] = i;
    tab[i] = x[id[i]];
  }
  int l = 0, r = 1e9, mid, ans = -1;
  while (l <= r) {
    mid = (l + r) >> 1;
    if (check(mid)) {
      ans = mid;
      l = mid + 1;
    }
    else r = mid - 1;
  }
  printf("%d\n", ans + 1);
  return 0;
}
