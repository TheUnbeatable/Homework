#include <bits/stdc++.h>
using namespace std;

const int N = 1050;
const int S = N - 1, T = N - 2;

namespace CostFlow {
#define travel(x, i) for (int i = fir[x]; i; i = e[i].nxt)
  struct edge {
    int nxt, to, cap, len;
  } e[3000000];
  int fir[N], lst[N], cnt = 1;
  long long dis[N];
  bool inq[N], vis[N];
  
  inline void addedge(int x, int y, int c, int l) {
    if (!x || !y || !c || x == y) return;
    e[++ cnt] = (edge) { fir[x], y, c, l }; fir[x] = cnt;
    e[++ cnt] = (edge) { fir[y], x, 0, -l }; fir[y] = cnt;
  }
  inline long long SPFA(int s, int t) {
    memset(dis, 0x3f, sizeof dis);
    memcpy(lst, fir, sizeof fir);
    queue <int> Q;
    Q.push(s); dis[s] = 0;
    while (Q.size()) {
      int x = Q.front(); Q.pop();
      inq[x] = 0;
      travel(x, i)
        if (e[i].cap && dis[x] + e[i].len < dis[e[i].to]) {
          dis[e[i].to] = dis[x] + e[i].len;
          if (!inq[e[i].to]) {
            Q.push(e[i].to); inq[e[i].to] = 1;
          }
        }
    }
    return dis[t];
  }
  inline int Dfs(int x, int t, int flow) {
    if (!flow || x == t) return flow;
    vis[x] = 1;
    int res = 0;
    for (int &i = lst[x]; i; i = e[i].nxt)
      if (!vis[e[i].to] && e[i].cap && dis[e[i].to] == dis[x] + e[i].len) {
        int tmp = Dfs( e[i].to, t, min(flow, e[i].cap) );
        flow -= tmp; res += tmp;
        e[i].cap -= tmp; e[i ^ 1].cap += tmp;
        if (!flow) break;
      }
    vis[x] = 0;
    if (!res) dis[x] = 1e9;
    return res;
  }
  inline long long minCost(int s, int t) {
    long long res = 0, dis;
    while ((dis = SPFA(s, t)) < 1e14)
      res += dis * Dfs(s, t, 1 << 29);
    return res;
  }
}
using CostFlow :: addedge;
using CostFlow :: minCost;

struct DirectionBoard {
private:
  int id[22][22];
public:
  inline int getMinimum(vector <string> board) {
    int n = board.size(), m = board[0].size();
    int clo = 0;
    for (int i = 1; i <= n; i ++)
      for (int j = 1; j <= m; j ++) {
        id[i][j] = ++ clo;
        addedge(S, clo, 1, 0);
        addedge(clo + n * m, T, 1, 0);
      }
    for (int i = 1; i <= n; i ++) {
      id[i][0] = id[i][m];
      id[i][m + 1] = id[i][1];
    }
    for (int j = 1; j <= m; j ++) {
      id[0][j] = id[n][j];
      id[n + 1][j] = id[1][j];
    }
    map <char, pair <int, int> > f;
    f['U'] = make_pair(-1, 0);
    f['D'] = make_pair(1, 0);
    f['L'] = make_pair(0, -1);
    f['R'] = make_pair(0, 1);
    for (int i = 1; i <= n; i ++)
      for (int j = 1; j <= m; j ++)
        for (map <char, pair <int, int> > :: iterator it = f.begin(); it != f.end(); it ++) {
          int k = id[i + it -> second.first][j + it -> second.second] + clo;
          if (it -> first == board[i - 1][j - 1]) addedge(id[i][j], k, 1, 0);
          else addedge(id[i][j], k, 1, 1);
        }
    return (int)minCost(S, T);
  }
};
