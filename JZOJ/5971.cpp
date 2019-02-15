#include <bits/stdc++.h>
using namespace std;

const int N = 210;

struct edge {
  int nxt, to;
} e[N << 1];
int fir[N], cnt = 1;
int n, dp[N][N][N], sz[N], le[N], ri[N], tsz[N], clo, fa[N], dep[N];
char s[N];

inline void addedge(int x, int y) {
  e[++ cnt] = (edge) { fir[x], y }; fir[x] = cnt;
}

inline int mabs(int x) { return x < 0 ? - x : x; }

inline void chkmin(int &x, int y) { if (x > y) x = y; }

inline void Dfs(int x, int f) {
  fa[x] = f;
  dep[x] = dep[f] + 1;
  le[x] = ++ clo;
  sz[x] = s[x] - '0';
  tsz[x] = 1;
  vector <int> to;
  for (int i = fir[x]; i; i = e[i].nxt)
    if (e[i].to != f) {
      Dfs(e[i].to, x);
      to.push_back(e[i].to);
      sz[x] += sz[e[i].to];
      tsz[x] += tsz[e[i].to];
    }
  dp[x][to.size()][0] = 0;
  dp[x][to.size()][1] = 0;
  for (int i = (int)to.size() - 1; ~ i; i --) {
    int y = to[i];
    for (int j = 0; j <= n; j ++)
      for (int k = 0; k <= tsz[y] && k <= j; k ++) {
        if (k && j == k) continue;
        chkmin(dp[x][i][j], dp[x][i + 1][j - k] + mabs(sz[y] - k) + dp[y][0][k]);
      }
  }
  ri[x] = clo;
}

inline int dis(int x, int y) {
  int res = 0;
  for (; le[y] < le[x] || le[y] > ri[x]; x = fa[x]) res ++;
  return res + dep[y] - dep[x];
}

int main() {
  freopen("party.in", "r", stdin);
  freopen("party.out", "w", stdout);
  memset(dp, 0x3f, sizeof dp);
  scanf("%d", &n);
  scanf("%s", s + 1);
  for (int i = 1, x, y; i < n; i ++) {
    scanf("%d%d", &x, &y);
    addedge(x, y); addedge(y, x);
  }
  Dfs(1, 0);
  int ans = 1e9;
  for (int i = 1; i <= n; i ++) {
    int cost = dp[i][0][sz[1]];
    for (int j = 1; j <= n; j ++)
      if ( s[j] == '1' && (le[j] < le[i] || le[j] > ri[i]) ) cost += dis(i, j);
    ans = min(ans, cost);
  }
  printf("%d\n", ans);
  return 0;
}
