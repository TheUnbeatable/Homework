#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 2e5 + 50;

struct edge {
  int nxt, to;
} e[N << 1];
int fir[N], cnt, clo;
int le[N], ri[N], n;

namespace Seg {
#define mid ((L + R) >> 1)
  int tag[N << 2];
  long long sum[N << 2];
  inline void Init() {
    memset(tag, 0, sizeof tag);
    memset(sum, 0, sizeof sum);
  }
  inline void Up(int x) {
    sum[x] = sum[x << 1] + sum[x << 1 | 1];
  }
  inline void Down(int x, int L, int R) {
    if (!tag[x]) return;
    tag[x << 1] += tag[x];
    tag[x << 1 | 1] += tag[x];
    sum[x << 1] += 1ll * tag[x] * (mid - L + 1);
    sum[x << 1 | 1] += 1ll * tag[x] * (R - mid);
    tag[x] = 0;
  }
  inline void Add(int l, int r, int v, int x = 1, int L = 1, int R = 2e5) {
    if (l <= L && R <= r) {
      tag[x] += v;
      sum[x] += v * (R - L + 1);
      return;
    }
    Down(x, L, R);
    if (l <= mid) Add(l, r, v, x << 1, L, mid);
    if (r > mid) Add(l, r, v, x << 1 | 1, mid + 1, R);
    Up(x);
  }
  inline long long Query(int l, int r, int x = 1, int L = 1, int R = 2e5) {
    if (l <= L && R <= r) return sum[x];
    Down(x, L, R);
    long long ans = 0;
    if (l <= mid) ans = Query(l, r, x << 1, L, mid);
    if (r > mid) ans += Query(l, r, x << 1 | 1, mid + 1, R);
    return ans;
  }
#undef mid
}

namespace LCT {
#define dir(x) (x == ch[fa[x]][1])
#define isroot(x) ( !fa[x] || ( x != ch[fa[x]][0] && x != ch[fa[x]][1] ) )
  int fa[N], ch[N][2];
  
  inline void Init() {
    memset(fa, 0, sizeof fa);
    memset(ch, 0, sizeof ch);
  }
  inline void link(int x, int f, int d) {
    if (x) fa[x] = f;
    if (f) ch[f][d] = x;
  }
  inline void rotate(int x) {
    int f = fa[x], d = (x == ch[f][1]);
    if (isroot(f)) fa[x] = fa[f];
    else link(x, fa[f], dir(f));
    link(ch[x][!d], f, d);
    link(f, x, !d);
  }
  inline void splay(int x) {
    for (; !isroot(x); rotate(x))
      if ( !isroot(fa[x]) ) rotate( dir(fa[x]) == dir(x) ? fa[x] : x );
  }
  inline int goleft(int x) {
    while (ch[x][0]) x = ch[x][0]; splay(x); return x;
  }
  inline void access(int x) {
    for (int y = 0, rc; x; y = x, x = fa[x]) {
      splay(x); rc = ch[x][1];
      if (y) {
        y = goleft(y);
        Seg :: Add(le[y], ri[y], -1);
      }
      ch[x][1] = y;
      if (rc) {
        rc = goleft(rc);
        Seg :: Add(le[rc], ri[rc], 1);
      }
    }
  }
}

inline void addedge(int x, int y) {
  e[++ cnt] = (edge) { fir[x], y }; fir[x] = cnt;
}

inline void Dfs(int x, int f) {
  LCT :: fa[x] = f;
  le[x] = ++ clo;
  for (int i = fir[x]; i; i = e[i].nxt)
    if (e[i].to != f) Dfs(e[i].to, x);
  ri[x] = clo;
  if (f)
    Seg :: Add(le[x], ri[x], 1);
}

inline void Occupy() {
  int u; scanf("%d", &u); LCT :: access(u + 1);
}

inline void Query() {
  int u; scanf("%d", &u); u ++;
  printf("%.10lf\n", 1.0 * Seg :: Query(le[u], ri[u]) / (ri[u] - le[u] + 1));
}

inline void solve() {
  Seg :: Init(); LCT :: Init();
  scanf("%d", &n);
  memset(fir, 0, sizeof fir); cnt = 1;
  for (int i = 1, x, y; i < n; i ++) {
    scanf("%d%d", &x, &y); x ++; y ++;
    addedge(x, y); addedge(y, x);
  }
  clo = 0; Dfs(1, 0);
  int q;
  scanf("%d", &q);
  for (char opt[10]; q; q --) {
    scanf("%s", opt);
    if (opt[0] == 'O') Occupy();
    else Query();
  }
}

int main() {
  int T;
  scanf("%d", &T);
  while (T --) solve();
  return 0;
}
