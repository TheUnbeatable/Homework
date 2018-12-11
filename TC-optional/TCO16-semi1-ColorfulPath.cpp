#include <bits/stdc++.h>
using namespace std;

typedef vector <pair <int, int> > vpi;
const int N = 1050;
const int INF = 2e9;
const int S = N - 1, T = N - 2;
  
namespace Flow {
  struct edge {
    int nxt, to, cap;
  } e[N * N];
  int fir[N], lst[N], cnt = 1;
  int gap[N], d[N], n;
  
  inline void addedge(int x, int y, int c, int ic = 0) {
    if (!x || !y || x == y) return;
    e[++ cnt] = (edge) { fir[x], y, c }; fir[x] = cnt;
    e[++ cnt] = (edge) { fir[y], x, ic }; fir[y] = cnt;
  }
  inline void Bfs(int s, int t) {
    queue <int> Q;
    memset(d, 0, sizeof d);
    memset(gap, 0, sizeof gap);
    memcpy(lst, fir, sizeof fir);
    Q.push(t);
    d[t] = gap[1] = 1;
    int x; n = 0;
    while (!Q.empty()) {
      n ++;
      x = Q.front();
      Q.pop();
      for (int i = fir[x]; i; i = e[i].nxt)
        if (!d[e[i].to]) {
          d[e[i].to] = d[x] + 1;
          gap[d[e[i].to]] ++;
          Q.push(e[i].to);
        }
    }
  }
  inline int Dfs(int u, int t, int flow) {
    if (u == t) return flow;
    int ret = 0, tmp;
    for (int &i = lst[u]; i; i = e[i].nxt)
      if (d[u] == d[e[i].to] + 1) {
        tmp = Dfs( e[i].to, t, min(flow, e[i].cap) );
        flow -= tmp; ret += tmp;
        e[i].cap -= tmp; e[i ^ 1].cap += tmp;
        if (!flow) return ret;
      }
    gap[d[u]] --;
    if (!gap[d[u]]) d[0] = n + 1;
    lst[u] = fir[u];
    gap[++ d[u]] ++;
    return ret;
  }
  inline long long maxFlow(int s, int t) {
    long long ret = 0;
    Bfs(s, t);
    while (d[s] <= n && d[0] <= n && ret < INF)
      ret += Dfs(s, t, INF);
    return ret;
  }
}
using Flow :: addedge;
using Flow :: maxFlow;

int n, m, q, Sz;

typedef vector <int> vi;

class ColorfulPath {
private:
  int c[N];
  vi col[2000], G[N], w[N];
  int bra[N][N];
public:
  inline void build(int l, int r, int fa) {
    for(int x = l; x < r; ) {
      int y = 0, p = 0, m = G[x].size();
      if (x != l)
        col[c[x]].push_back(fa);
      for (int i = 0; i < m; ++i) {
        if(G[x][i] > y) {
          y = G[x][i]; p = i;
        }
      } if (!y) {
        addedge(fa, T, INF);
        for(int i = l + 1; i < r; ++i)
          col[c[i]].push_back(fa);
        return;
      } else {
        G[x][p] = 0;
        ++ Sz;
        addedge(fa, Sz, w[x][p], INF);
        build(x, y, Sz); x = y;
      }
    }
  }
  inline int shortestPath(vi a, vi b, vi cost, vi color) {
    n = color.size();
    m = a.size();
    memset(bra, 0x3f, sizeof bra);
    for (int i = 0; i < m; i ++)
      bra[a[i]][b[i]] = min(bra[a[i]][b[i]], cost[i]);
    for (int i = 0; i <= n + 1; i ++)
      for (int j = i + 1; j <= n + 1; j ++)
        if (bra[i][j] < 1e9) {
          G[i].push_back(j);
          w[i].push_back(bra[i][j]);
        }
    for (int i = 0; i < n; i ++)
      c[i + 1] = color[i];
    build(0, n + 1, S);
    for (int i = 1; i <= 1000; i ++) {
      vi &c = col[i];
      for (int j = 1; j < (int) c.size(); j ++)
        addedge(c[j], c[j - 1], INF, INF);
    }
    long long ans = maxFlow(S, T);
    if (ans < INF) return ans;
    else return -1;
  }
};
