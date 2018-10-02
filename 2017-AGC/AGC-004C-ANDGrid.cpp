#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <queue>
#define rep(i, x, y) for (int i = x; i <= y; i ++)
using namespace std;

const int N = 505;

char G[N][N];
bool cho[N][N];

int main() {
  int n, m, t = 0;
  scanf("%d%d", &n, &m);
  rep(i, 1, n) scanf("%s", G[i] + 1);
  rep(i, 1, n) cho[i][1] = 1;
  for (int i = 1; i <= n; i += 2)
    rep(j, 1, m - 1) cho[i][j] = 1;
  rep(i, 1, n) {
    rep(j, 1, m) {
      if (G[i][j] == '#' || cho[i][j]) putchar('#');
      else putchar('.');
    }
    putchar('\n');
  }
  putchar('\n');
  rep(i, 1, n) {
    rep(j, 1, m) {
      if (G[i][j] == '#' || !cho[i][j]) putchar('#');
      else putchar('.');
    }
    putchar('\n');
  }
  return 0;
}
