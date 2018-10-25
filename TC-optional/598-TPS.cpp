#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <string>
#include <vector>
using namespace std;

const int N = 55;

class TPS {
private:
  struct edge {
    int nxt, to;
  } e[N << 1];
  int fir[N], cnt = 1, n;
  int f[N], g[N];
  inline void addedge(int x, int y) {
    e[++ cnt] = (edge) { fir[x], y }; fir[x] = cnt;
  }
  inline void Dfs(int x, int fa) {
    int zero = 0, one = 0, cnt = 0;
    for (int i = fir[x]; i; i = e[i].nxt)
      if (e[i].to != fa) {
        cnt ++;
        Dfs(e[i].to, x);
        one = min(one + g[e[i].to], zero + f[e[i].to]);
        zero += g[e[i].to];
      }
    if (cnt == 0) {
      f[x] = 0; g[x] = 1;
    } else if (cnt == 1) {
      f[x] = one;
      g[x] = min(zero, one + 1);
    } else {
      f[x] = 1e9;
      g[x] = min(zero, one);
    }
  }
public:
  inline int minimalBeacons(vector <string> linked) {
    n = linked.size();
    if (n == 1) return 0;
    for (int i = 0; i < n; i ++)
      for (int j = 0; j < n; j ++)
        if (linked[i][j] == 'Y') addedge(i + 1, j + 1);
    int ans = n;
    for (int i = 1; i <= n; i ++) {
      Dfs(i, 0);
      ans = min(ans, min(f[i], g[i]) + 1);
    }
    return ans;
  }
};
