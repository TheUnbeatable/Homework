#include <cstdio>
#include <iostream>
#include <cmath>
#include <cstring>
#include <algorithm>
using namespace std;
 
typedef long long LL;
const int N = 1600;
const double PI = acos(-1);
 
struct Point {
  int x, y;
  double alp;
  Point(int _x = 0, int _y = 0) : x(_x), y(_y) {}
   
  inline Point operator + (const Point &o) const {
    return Point(x + o.x, y + o.y);
  }
  inline Point operator - (const Point &o) const {
    return Point(x - o.x, y - o.y);
  }
  inline LL operator ^ (const Point &o) const {
    return (LL)x * o.y - (LL)y * o.x;
  }
  inline bool operator < (const Point &o) const {
    return alp < o.alp;
  }
  inline double degree() {
    return atan2(y, x);
  }
  inline void read() {
    scanf("%d%d", &x, &y);
  }
} A[N], B[N], p[N];
 
LL ans = 0;
int n, m, K;
 
inline void solve(const Point &b) {
  static int val[N];
  static Point u[N], d[N], aa[N], pp;
  int uu = 0, dd = 0;
  memset(val, 0, sizeof val);
  for (int i = 1; i <= n; i ++) {
    aa[i] = A[i]; aa[i].alp = (A[i] - b).degree();
  }
  for (int i = 1; i <= K; i ++) {
    pp = p[i]; pp.alp = (p[i] - b).degree();
    if (pp.y >= b.y) u[++ uu] = pp;
    else d[++ dd] = pp;
  }
  sort(u + 1, u + uu + 1);
  sort(d + 1, d + dd + 1);
  sort(aa + 1, aa + n + 1);
  int tot = 0, tmp;
  for (int i = 1, j = 0; i <= uu; i ++) {
    while (aa[j + 1].alp < u[i].alp && j < n) j ++;
    val[i] = j; tot += j;
  }
  tmp = tot;
  for (int i = 1; i <= uu; i ++) {
    tot -= val[i];
    ans += tot - val[i] * (uu - i);
  }
  tot = tmp;
  for (int i = dd, j = uu; i >= 1; i --) {
    while (((d[i] - b) ^ (u[j] - b)) < 0 && j > 0) tot -= val[j], j --;
    ans += tot;
  }
  reverse(u + 1, u + uu + 1);
  reverse(aa + 1, aa + n + 1);
  tot = 0;
  for (int i = 1, j = 0; i <= uu; i ++) {
    while (aa[j + 1].alp > u[i].alp && j < n) j ++;
    val[i] = j; tot += j;
  }
  for (int i = 1, j = uu; i <= dd; i ++) {
    while (((u[j] - b) ^ (d[i] - b)) < 0 && j > 0) tot -= val[j], j --;
    ans += tot;
  }
}
 
int main() {
#ifdef ONLINE_JUDGE
  freopen("ambitious.in", "r", stdin);
  freopen("ambitious.out", "w", stdout);
#endif
  for (; ; ) {
    scanf("%d", &n);
    if (!n) break;
    ans = 0;
    for (int i = 1; i <= n; i ++) A[i].read();
    scanf("%d", &m);
    for (int i = 1; i <= m; i ++) B[i].read();
    scanf("%d", &K);
    for (int i = 1; i <= K; i ++) p[i].read();
    for (int i = 1; i <= m; i ++) solve(B[i]);
    printf("%lld\n", ans);
  }
  return 0;
}
