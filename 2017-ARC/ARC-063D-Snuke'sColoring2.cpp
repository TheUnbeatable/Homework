#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 3e5 + 50;

namespace Tree {
#define mid ((L + R) >> 1)
#define x ID(L, R)
#define lc ID(L, mid)
#define rc ID(mid + 1, R)
  int __key[N << 1], __lazy[N << 1];

  inline int ID(int L, int R) {return (L + R) | (L != R);}
  inline void Init() {
    memset(__key, 0, sizeof __key);
    memset(__lazy, 0, sizeof __lazy);
  }
  inline void PushDown(int L, int R) {
    if (!__lazy[x]) return;
    __lazy[lc] += __lazy[x];
    __lazy[rc] += __lazy[x];
    __key[lc] += __lazy[x];
    __key[rc] += __lazy[x];
    __lazy[x] = 0;
  }
  inline void Add(int L, int R, int l, int r, int val) {
    if (l > r || !val) return;
    if (L == l && R == r) {
      __key[x] += val;
      __lazy[x] += val;
      return;
    }
    PushDown(L, R);
    if (r <= mid) Add(L, mid, l, r, val);
    else if (l > mid) Add(mid + 1, R, l, r, val);
    else {
      Add(L, mid, l, mid, val);
      Add(mid + 1, R, mid + 1, r, val);
    }
    __key[x] = max(__key[lc], __key[rc]);
  }

#undef mid
#undef x
#undef lc
#undef rc
}
using namespace Tree;

inline void Read(int &x) {
  x = 0; char ch;
  while (!isdigit(ch = getchar()));
  do {x = (x << 1) + (x << 3) + ch - '0';} while (isdigit(ch = getchar()));
}

int W, H, n;
int x[N], y[N], id[N], rnk[N];
int topU, topD, ans;
pair <int, int> U[N], D[N];

inline bool cmp(int a, int b) {
  return x[a] < x[b];
}

inline void solve() {
  Tree::Init();
  for (int i = 1; i <= n; i ++) id[i] = i;
  sort(id + 1, id + n + 1, cmp);
  int mid = H >> 1, m = n + 10;
  topU = topD = 1;
  U[1].first = D[1].first = 1;
  U[1].second = H; D[1].second = 0;
  Tree::Add(1, m, 1, 1, H);
  for (int l = 1, r = 1, i = 2; l <= n; l = r, i ++) {
    Tree::Add(1, m, 1, i - 1, x[id[l]] - x[id[l - 1]]);
    ans = max(ans, Tree::__key[Tree::ID(1, m)]);
    int up = H, down = 0, p = 0;
    while (x[id[r]] == x[id[l]] && r <= n) {
      if (y[id[r]] > mid) up = min(up, y[id[r]]);
      else down = max(down, y[id[r]]);
      r ++;
    }
    Tree::Add(1, m, i, i, H);
    while (topU && U[topU].second >= up) {
      Add(1, m, U[topU - 1].first + 1, U[topU].first, up - U[topU].second);
      topU --;
    }
    U[++ topU] = make_pair(i - 1, up);
    U[++ topU] = make_pair(i, H);
    while (topD && D[topD].second <= down) {
      Add(1, m, D[topD - 1].first + 1, D[topD].first, D[topD].second - down);
      topD --;
    }
    D[++ topD] = make_pair(i - 1, down);
    D[++ topD] = make_pair(i, 0);
  }
  ans = max(ans, Tree::__key[Tree::ID(1, m)] + W - x[id[n]]);
}

int main() {
  Read(W); Read(H); Read(n);
  for (int i = 1; i <= n; i ++) Read(x[i]), Read(y[i]);
  solve();
  swap(W, H);
  for (int i = 1; i <= n; i ++) swap(x[i], y[i]);
  solve();
  printf("%d\n", ans * 2);
  return 0;
}
