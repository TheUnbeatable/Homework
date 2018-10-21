#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;

typedef long long LL;
const int N = 550;

struct vec {
  LL x, y;
  vec() {}
  vec(LL _x, LL _y) : x(_x), y(_y) {}
  inline void read() {
    scanf("%lld%lld", &x, &y);
  }
  inline vec operator - (const vec &o) {
    return vec (x - o.x, y - o.y);
  }
  inline LL operator ^ (const vec &o) {
    return x * o.y - y * o.x;
  }
} a[N];

int n;
bool G[N][N];
vector <int> dp[N][N];

inline void Dfs(int L, int R) {
  if (L > R || dp[L][R].size()) return;
  vector <int> &cur = dp[L][R];
  cur.push_back(L);
  for (int i = L + 1, j; i <= R; i ++) {
    if (G[L][i]) continue;
    for (j = i; !G[L][j] && j <= R; j ++);
    Dfs(i, j - 1);
    for (auto k : dp[i][j - 1]) cur.push_back(k);
    i = j - 1;
  }
  Dfs(L + 1, R);
  if (cur.size() < dp[L + 1][R].size()) cur = dp[L + 1][R];
}

int main() {
#ifdef ONLINE_JUDGE
  freopen("hide.in", "r", stdin);
  freopen("hide.out", "w", stdout);
#endif
  while (scanf("%d", &n), n) {
    for (int i = 1; i <= n; i ++) {
      a[i].read();
      for (int j = 1; j <= n; j ++)
        G[i][j] = 0, dp[i][j].clear();
    }
    for (int i = 2; i < n; i ++) {
      G[i][i + 1] = G[i + 1][i] = 1;
      vec Max = a[i + 1] - a[i];
      for (int j = i + 2; j <= n; j ++) {
        vec cur = a[j] - a[i];
        if ((Max ^ cur) >= 0) {
          G[i][j] = G[j][i] = 1;
          Max = cur;
        }
      }
    }
    Dfs(2, n);
    printf("%d\n", (int) dp[2][n].size());
    for (auto it : dp[2][n]) printf("%d ", it);
    puts("");
  }
  return 0;
}
