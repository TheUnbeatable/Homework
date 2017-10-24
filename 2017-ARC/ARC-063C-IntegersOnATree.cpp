#include <cstdio>
#include <iostream>
#include <cstdlib>
#define L first
#define R second
#define travel(x, i) for (int i = fir[x]; i; i = e[i].nxt)
#define fail {puts("No"); exit(0);}
using namespace std;
 
const int N = 1e5 + 5;
const int INF = 1e7;
 
struct Constraint {
  pair <int, int> range;
  bool o, u;
  Constraint() {u = 0; range.L = - INF; range.R = INF;}
} con[N];
 
struct edge {
  int nxt, to;
} e[N << 1];
 
int fir[N], cnt = 0;
int n, k, col[N];
bool done[N];
 
inline void add(int x, int y) {
  e[++ cnt] = (edge){fir[x], y};
  fir[x] = cnt;
}
 
inline void combine(Constraint &A, const Constraint &B) {
  if (!B.u) return;
  if (!A.u) {
    A.u = 1;
    A.range = B.range;
    A.range.L --;
    A.range.R ++;
    return;
  }
  A.range.L = max(A.range.L, B.range.L - 1);
  A.range.R = min(A.range.R, B.range.R + 1);
}
 
inline void dfs(int x, int pa) {
  if (done[x]) {
    con[x].u = 1;
    con[x].range.L = con[x].range.R = col[x];
    con[x].o = col[x] & 1;
  }
  travel(x, i)
    if (e[i].to != pa) {
      dfs(e[i].to, x);
      if (con[x].u && con[e[i].to].u && con[x].o == con[e[i].to].o) fail
      if (con[e[i].to].u) con[x].o = con[e[i].to].o ^ 1;
      combine(con[x], con[e[i].to]);
      if (con[x].range.L > con[x].range.R) fail
    }
}
 
inline void solve(int x, int pa) {
  if (!done[x]) {
    if (con[x].range.L <= col[pa] + 1 && col[pa] + 1 <= con[x].range.R) col[x] = col[pa] + 1;
    else col[x] = col[pa] - 1;
    con[x].range.R = con[x].range.L = col[x];
    con[x].u = 1;
  }
  travel(x, i)
    if (e[i].to != pa) {
      combine(con[e[i].to], con[x]);
      solve(e[i].to, x);
    }
}
 
int main() {
  scanf("%d", &n);
  for (int i = 1, x, y; i < n; i ++) {
    scanf("%d%d", &x, &y);
    add(x, y); add(y, x);
  }
  scanf("%d", &k);
  int rt = 0;
  for (int i = 1, p, v; i <= k; i ++) {
    scanf("%d%d", &v, &p);
    if (i == 1) rt = v;
    col[v] = p;
    done[v] = 1;
  }
  dfs(rt, 0);
  puts("Yes");
  solve(rt, 0);
  for (int i = 1; i <= n; i ++) printf("%d\n", col[i]);
  return 0;
}
