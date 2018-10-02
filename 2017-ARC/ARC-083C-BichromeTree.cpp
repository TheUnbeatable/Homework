#include <cstdio>
#include <iostream>
#include <cstring>
#include <cstdlib>
#define travel(x, i) for (int i = fir[x]; i; i = e[i].nxt)
using namespace std;

const int N = 1005;

struct edge {
  int nxt, to;
}e[N];
int fir[N], cnt = 0;

int X[N], Y[N];

inline void add(int x, int y) {
  e[++ cnt] = (edge){fir[x], y};
  fir[x] = cnt;
}

inline void dfs(int x) {
  int judge = 0;
  travel(x, i) dfs(e[i].to), judge += min(Y[e[i].to], X[e[i].to]);
  if (judge > X[x]) {
    puts("IMPOSSIBLE");
    exit(0);
  }
  static int dp[2][5005];
  memset(dp[0], 0, sizeof(int) * (X[x] + 2));
  int cur = 0, nxt = 1, y;
  travel(x, i) {
    y = e[i].to;
    nxt = cur ^ 1;
    memset(dp[nxt], 0x7f, sizeof(int) * (X[x] + 2));
    for (int i = 0; i <= X[x]; i ++) {
      if (i + X[y] <= X[x]) dp[nxt][i + X[y]] = min(dp[nxt][i + X[y]], dp[cur][i] + Y[y]);
      if (i + Y[y] <= X[x]) dp[nxt][i + Y[y]] = min(dp[nxt][i + Y[y]], dp[cur][i] + X[y]);
    }
    cur = nxt;
  }
  Y[x] = 1000000;
  for (int i = 0; i <= X[x]; i ++) Y[x] = min(Y[x], dp[cur][i]);
}

int main() {
  int n, x;
  scanf("%d", &n);
  for (int i = 2; i <= n; i ++) {scanf("%d", &x); add(x, i);}
  for (int i = 1; i <= n; i ++) scanf("%d", &X[i]);
  dfs(1);
  puts("POSSIBLE");
  return 0;
}
