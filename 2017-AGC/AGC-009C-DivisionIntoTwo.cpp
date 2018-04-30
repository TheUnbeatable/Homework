#include <cstdio>
#include <iostream>
#include <cstring>
using namespace std;

typedef long long LL;
const int N = 1e5 + 50;
const int mod = 1e9 + 7;

inline void Inc(int &x, int y) {
  if ((x += y) >= mod) x -= mod;
}

struct BIT {
  int a[N];
  BIT() { memset(a, 0, sizeof a); }
  inline void add(int x, int val) {
    for (; x < N; x += x & (- x)) Inc(a[x], val);
  }
  inline int Sum(int x) {
    int res = 0;
    for (; x > 0; x -= x & (- x)) Inc(res, a[x]);
    return res;
  }
  inline void Add(int l, int r, int val) {
    l = max(l, 1);
    if (l > r) return;
    add(l, val); add(r + 1, mod - val);
  }
} F, G;

int n;
LL A, B, a[N], ra[N], rb[N];

int main() {
  scanf("%d%lld%lld", &n, &A, &B);
  for (int i = 1; i <= n; i ++) scanf("%lld", &a[i]);
  a[0] = - 2e18;
  a[n + 1] = 2e18;
  ra[n] = rb[n] = n;
  for (int i = n - 1; ~ i; i --) {
    ra[i] = rb[i] = i;
    if (a[i + 1] - a[i] >= A) ra[i] = ra[i + 1];
    if (a[i + 1] - a[i] >= B) rb[i] = rb[i + 1];
  }
  int f, g;
  for (int i = 0, pa = 1, pb = 1; i <= n; i ++) {
    f = i ? F.Sum(i) : 1;
    g = i ? G.Sum(i) : 1;
    while (pa <= n + 1 && a[pa] - a[i] < A) pa ++;
    while (pb <= n + 1 && a[pb] - a[i] < B) pb ++;
    if (pa <= n + 1) G.Add(pa - 1, rb[i + 1], f);
    if (pb <= n + 1) F.Add(pb - 1, ra[i + 1], g);
  }
  Inc(f, g);
  printf("%d\n", f);
  return 0;
}
