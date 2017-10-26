#include <cstdio>
#include <iostream>
using namespace std;

const int N = 2e5 + 5;

struct edge {
  int nxt, to;
} e[N];
int fir[N], a[N];

namespace Segment_Tree {
#define mid ((L + R) >> 1)
#define no ID(L, R)
#define lc ID(L, mid)
#define rc ID(mid + 1, R)
  int key[N << 1], lazy[N << 1];
  inline int ID(int L, int R) {return (L + R) | (L != R);}
  inline void PushDown(int L, int R) {
    if (!lazy[no] || L == R) return;
    lazy[lc] += lazy[no];
    lazy[rc] += lazy[no];
    key[lc] += lazy[no];
    key[rc] += lazy[no];
    lazy[no] = 0;
  }
  inline void PushUp(int L, int R) {
    key[no] = max(key[lc], key[rc]);
  }
  inline void Init(int L, int R) {
    lazy[no] = 0;
    if (L == R) {
      key[no] = L;
      return;
    }
    Init(L, mid);
    Init(mid + 1, R);
    PushUp(L, R);
  }
  inline void Add(int L, int R, int l, int r) {
    if (L == l && R == r) {
      key[no] ++;
      lazy[no] ++;
      return;
    }
    PushDown(L, R);
    if (r <= mid) Add(L, mid, l, r);
    else if (l > mid) Add(mid + 1, R, l, r);
    else {
      Add(L, mid, l, mid);
      Add(mid + 1, R, mid + 1, r);
    }
    PushUp(L, R);
  }
  inline int Max(int L, int R, int l, int r) {
    if (L == l && R == r) return key[no];
    PushDown(L, R);
    if (r <= mid) return Max(L, mid, l, r);
    else if (l > mid) return Max(mid + 1, r, l, r);
    else return max(Max(L, mid, l, mid), Max(mid + 1, R, mid + 1, r));
  }
#undef mid
#undef no
#undef lc
#undef rc
}
using namespace Segment_Tree;

int main() {
  int ans, n, m;
  scanf("%d%d", &n, &m);
  ans = max(0, n - m);
  for (int i = 1, l, r; i <= n; i ++) {
    scanf("%d%d", &l, &r);
    e[i] = (edge){fir[l], r};
    fir[l] = i;
  }
  Segment_Tree::Init(0, m + 1);
  for (int i = 0; i <= m; i ++) {
    for (int j = fir[i]; j; j = e[j].nxt)
      Segment_Tree::Add(0, m + 1, 0, e[j].to);
    ans = max(ans, Segment_Tree::Max(0, m + 1, i + 1, m + 1) - m - i - 1);
  }
  printf("%d\n", ans);
  return 0;
}
