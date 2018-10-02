#include <cstdio>
#include <iostream>
#include <algorithm>
#define fir first
#define sec second
#define mid ((L + R) >> 1)
using namespace std;

const int N = 3e5 + 5;
const int M = 7e6 + 6;

int n, m, base = 0;
pair <int, int> seg[N];
int rt[N], lc[M], rc[M], key[M], S = 0;

template <typename T> void Read(T &x) {
  x = 0; char ch;
  while (!isdigit(ch = getchar()));
  do {x = (x << 1) + (x << 3) + ch - '0';} while (isdigit(ch = getchar()));
}

inline void add(int x, int y, int L, int R, int p) {
  key[y] = key[x] + 1;
  if (L == R) return;
  if (p <= mid) {
    rc[y] = rc[x];
    lc[y] = ++ S;
    add(lc[x], lc[y], L, mid, p);
  }
  else {
    lc[y] = lc[x];
    rc[y] = ++ S;
    add(rc[x], rc[y], mid + 1, R, p);
  }
}

inline int query(int x, int y, int L, int R, int low) {
  if (low > R) return 0;
  if (L == R) return key[y] - key[x];
  if (low <= mid) return query(lc[x], lc[y], L, mid, low) + key[rc[y]] - key[rc[x]];
  else return query(rc[x], rc[y], mid + 1, R, low);
}

int main() {
  int t = 0;
  Read(n); Read(m);
  for (int i = 1, l, r; i <= n; i ++) {
    Read(l); Read(r);
    if (l == 0) base ++;
    else seg[++ t] = make_pair(l, r);
  }
  sort(seg + 1, seg + t + 1);
  int p = 0;
  for (int i = 1, tmp; i <= t; i ++) {
    while (p < seg[i].fir) rt[p + 1] = rt[p], p ++;
    tmp = ++ S;
    add(rt[p], tmp, 1, m, seg[i].sec);
    rt[p] = tmp;
  }
  while (p < m) rt[p + 1] = rt[p], p ++;
  int ans = 0;
  for (int i = 1; i <= m; i ++) {
    ans = base;
    for (int j = 0; j <= m; j += i)
      ans += query(rt[j], rt[min(j + i, m)], 1, m, j + i);
    printf("%d\n", ans);
  }
  return 0;
}
