#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <map>
#include <cstdlib>
using namespace std;

const int N = 1e5 + 50;

int n;
int fa[N], a[N], b[N], top;
map <int, int> e[N];

inline int getf(int x) {
  return fa[x] ? fa[x] = getf(fa[x]) : x;
}

inline void Merge(int x, int y) {
  x = getf(x); y = getf(y);
  if (x == y) { puts("NO"); exit(0); }
  if (e[x].size() > e[y].size()) swap(x, y);
  fa[x] = y;
  int t;
  for (auto i : e[x]) {
    t = i.first;
    e[t].erase(x);
    if (e[y].count(t)) {
      if (e[y][t] != i.second) {
        a[++ top] = y; b[top] = t;
        e[y].erase(t);
        e[t].erase(y);
      }
      else {
        puts("NO"); exit(0);
      }
    }
    else {
      e[y][t] = i.second;
      e[t][y] = i.second;
    }
  }
}

int main() {
  scanf("%d", &n);
  for (int i = 1, u, v; i < n; i ++) {
    scanf("%d%d", &u, &v);
    e[u][v] = 1; e[v][u] = 1;
  }
  for (int i = 1, x, y; i < n; i ++) {
    scanf("%d%d", &x, &y);
    if (e[x].count(y)) {
      if (e[x][y] == 2) return 0 * puts("NO");
      e[x].erase(y);
      e[y].erase(x);
      a[++ top] = x; b[top] = y;
    }
    else {
      e[x][y] = 2; e[y][x] = 2;
    }
  }
  for (int i = 1; i <= top; i ++) Merge(a[i], b[i]);
  puts(top + 1 == n ? "YES" : "NO");
  return 0;
}
