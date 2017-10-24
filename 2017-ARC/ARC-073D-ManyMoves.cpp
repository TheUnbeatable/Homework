#include <cstdio>
#include <iostream>
#include <cstring>
#include <cmath>
#define INC 0
#define DEC 1
#define clr(x, y) memset(x, y, sizeof x)
using namespace std;

typedef long long LL;
const int N = 2e5 + 5;

namespace Segment_Tree {
#define mid ((L + R) >> 1)
#define no ID(L, R)
#define lc ID(L, mid)
#define rc ID(mid + 1, R)
  LL key[N << 1][2], lazy[N << 1];
  
  inline void Init() {
    clr(key, 0x0f);
    clr(lazy, 0);
  }
  
  inline int ID(int L, int R) {return (L + R) | (L != R);}
  
  inline void PushDown(int L, int R) {
    if (L == R || !lazy[no]) return;
    key[lc][0] += lazy[no];
    key[rc][0] += lazy[no];
    key[lc][1] += lazy[no];
    key[rc][1] += lazy[no];
    lazy[lc] += lazy[no];
    lazy[rc] += lazy[no];
    lazy[no] = 0;
  }

  inline void PushUp(int L, int R) {
    key[no][0] = min(key[lc][0], key[rc][0]);
    key[no][1] = min(key[lc][1], key[rc][1]);
  }
  
  inline void Update(int L, int R, int x, LL val) {
    if (L == R) {
      key[no][0] = min((LL)val + L, key[no][0]);
      key[no][1] = min((LL)val - L, key[no][1]);
      return;
    }
    PushDown(L, R);
    if (x <= mid) Update(L, mid, x, val);
    else Update(mid + 1, R, x, val);
    PushUp(L, R);
  }

  inline LL Query(int L, int R, int l, int r, bool type) {
    if (L == l && R == r) return key[no][type];
    PushDown(L, R);
    if (r <= mid) return Query(L, mid, l, r, type);
    else if (l > mid) return Query(mid + 1, R, l, r, type);
    else return min(Query(L, mid, l, mid, type), Query(mid + 1, R, mid + 1, r, type));
  }

  inline LL Solve(int L, int R) {
    if (L == R) return key[L][no] - L;
    PushDown(L, R);
    return min(Solve(L, mid), Solve(mid + 1, R));
  }
#undef mid
#undef no
#undef lc
#undef rc
}
using namespace Segment_Tree;

int main() {
  int n, q, a, b, pre;
  scanf("%d%d%d%d", &n, &q, &a, &b);
  Init();
  pre = a;
  Update(1, n, b, 0LL);
  LL tmp;
  for (int i = 1, x; i <= q; i ++) {
    scanf("%d", &x);
    tmp = min(Query(1, n, x, n, INC) - x, Query(1, n, 1, x, DEC) + x);
    lazy[ID(1, n)] += abs(x - pre);
    Update(1, n, pre, tmp);
    pre = x;
  }
  printf("%lld\n", Solve(1, n));
  return 0;
}
