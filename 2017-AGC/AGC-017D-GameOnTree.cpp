#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 1e5 + 50;

struct edge {
  int nxt, to;
} e[N << 1];
int fir[N], cnt = 1;

inline void addedge(int x, int y) {
  e[++ cnt] = (edge) { fir[x], y }; fir[x] = cnt;
}

int n;

inline int Dfs(int x, int f) {
  int sg = 0;
  for (int i = fir[x]; i; i = e[i].nxt)
    if (e[i].to != f) sg ^= Dfs(e[i].to, x) + 1;
  return sg;
}

int main() {
  scanf("%d", &n);
  for (int i = 1, x, y; i < n; i ++) {
    scanf("%d%d", &x, &y);
    addedge(x, y); addedge(y, x);
  }
  puts(Dfs(1, 0) ? "Alice" : "Bob");
  return 0;
}
