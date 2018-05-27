#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 500;

int n, h;
int in[N], out[N], fa[N];
bool self[N];

inline int getf(int x) {
  return fa[x] ? fa[x] = getf(fa[x]) : x;
}

inline void link(int x, int y) {
  x = getf(x); y = getf(y);
  if (x != y) fa[x] = y;
}

int main() {
  scanf("%d%d", &n, &h);
  for (int i = 1, a, b, c, d, p, q; i <= n; i ++) {
    scanf("%d%d%d%d", &a, &b, &c, &d);
    if (!c) p = h + a;
    else p = h - c;
    if (!d) q = h - b;
    else q = h + d;
    link(p, q);
    out[p] ++; in[q] ++;
    if (p == q) self[p] = 1;
  }
  for (int i = 0; i <= h + h; i ++) {
    if (i > h && in[i] > out[i]) return 0 * puts("NO");
    if (i < h && in[i] < out[i]) return 0 * puts("NO");
    bool fd = 0, fri = self[i];
    for (int j = 0; j <= h + h && !fd; j ++)
      if (getf(j) == getf(i)) {
        if (i != j) fri = 1;
        if (in[j] != out[j]) fd = 1;
      }
  if (!fd && fri) return 0 * puts("NO");
  }
  puts("YES");
  return 0;
}
