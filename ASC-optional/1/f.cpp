#include <cstdio>
#include <iostream>
#include <cmath>
#include <cstring>
#include <cstdlib>
using namespace std;

typedef long double LD;
const int N = 305;
const LD PI = acos(-1);
const LD eps = 1e-6;

inline int sgn(LD x) { return x < - eps ? -1 : (x > eps); }

struct Vector {
  LD x, y;
  Vector() {}
  Vector(LD _x, LD _y) : x(_x), y(_y) {}
  Vector(LD d) : x(cos(d)), y(sin(d)) {}
  
  inline void read() { scanf("%Lf%Lf", &x, &y); }
  inline Vector operator + (const Vector &o) const { return Vector(x + o.x, y + o.y); }
  inline Vector operator - (const Vector &o) const { return Vector(x - o.x, y - o.y); }
  inline Vector operator * (LD o) const { return Vector(x * o, y * o); }
  inline LD operator ^ (const Vector &o) const { return x * o.y - y * o.x; }
  inline LD norm() { return x * x + y * y; }
} o[N], p[N];
LD r[N];
bool G[N][N], ok;
int vis[N];
int sta[N], top, n;

inline void work_with(int x) {
  int k = 0;
  p[++ k] = o[x];
  for (int i = top; i > 0; i --) {
    p[++ k] = o[sta[i]];
    if (sta[i] == x) break;
  }
  Vector d = Vector(1235 / 10000.0 * 2 * PI);
  Vector s = o[n + 1], q = s + (d * 10000.0);
  int cnt = 0;
  for (int i = 1; i < k; i ++) {
    if (sgn(d ^ (p[i] - s)) * sgn(d ^ (p[i + 1] - s)) != -1) continue;
    if (sgn((p[i + 1] - p[i]) ^ (s - p[i])) * sgn((p[i + 1] - p[i]) ^ (q - p[i])) == -1) cnt ++;
  }
  if (cnt % 2) ok = 0;
}

inline void Dfs(int x, int fa) {
  if (!ok) return;
  vis[x] = 1;
  sta[++ top] = x;
  for (int i = 1; i <= n && ok; i ++)
    if (G[x][i] && i != fa) {
      if (vis[i] == 1) work_with(i);
      else if (!vis[i]) Dfs(i, x);
    }
  top --;
  vis[x] = 2;
}

int main() {
#ifdef ONLINE_JUDGE
  freopen("out.in", "r", stdin);
  freopen("out.out", "w", stdout);
#endif
  while (scanf("%d", &n) != EOF) {
    memset(G, 0, sizeof G);
    memset(vis, 0, sizeof vis);
    for (int i = 1; i <= n + 1; i ++)
      o[i].read(), scanf("%Lf", &r[i]);
    for (int i = 1; i <= n; i ++) r[i] += r[n + 1];
    for (int i = 1; i <= n; i ++)
      for (int j = i + 1; j <= n; j ++)
        if ((o[i] - o[j]).norm() < (r[i] + r[j]) * (r[i] + r[j])) G[i][j] = G[j][i] = 1;
    ok = 1;
    for (int i = 1; i <= n && ok; i ++)
      if (!vis[i]) top = 0, Dfs(i, 0);
    if (ok) puts("YES");
    else puts("NO");
  }
  return 0;
}
