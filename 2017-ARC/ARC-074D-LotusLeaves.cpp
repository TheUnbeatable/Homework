#include <cstdio>
#include <iostream>
#include <queue>
#include <cstring>
using namespace std;

const int V = 250;
const int E = 30000;
const int INF = 1e9;

namespace Graph {
#define travel(x, i) for (int i = fir[x]; i; i = e[i].nxt)
  static const int S = V - 1, T = V - 2;

  struct edge {
    int nxt, to, cap;
  } e[E];
  int fir[V], dis[V];

  inline void Init() {
    memset(fir, 0, sizeof fir);
  }
  
  inline void Add(int x, int y, int cto, int cback) {
    static int cnt = 1;
    e[++ cnt] = (edge){fir[x], y, cto};
    fir[x] = cnt;
    e[++ cnt] = (edge){fir[y], x, cback};
    fir[y] = cnt;
  }

  inline bool bfs() {
    queue <int> Q;
    memset(dis, -1, sizeof dis);
    dis[T] = 1;
    Q.push(T);
    int x;
    while (!Q.empty()) {
      x = Q.front();
      Q.pop();
      travel(x, i)
	if (e[i ^ 1].cap > 0 && dis[e[i].to] == -1) {
	  dis[e[i].to] = dis[x] + 1;
	  Q.push(e[i].to);
	}
    }
    return dis[S] != -1;
  }

  inline int dfs(int x, int flow) {
    if (!flow || x == T) return flow;
    int tmp, res = 0;
    travel(x, i)
      if (dis[e[i].to] == dis[x] - 1) {
	tmp = dfs(e[i].to, min(flow, e[i].cap));
	flow -= tmp;
	res += tmp;
	e[i].cap -= tmp;
	e[i ^ 1].cap += tmp;
	if (!flow) return res;
      }
    dis[x] = -1;
    return res;
  }
  
  inline int MaxFlow() {
    int ret = 0;
    while (bfs()) ret += dfs(S, INF);
    return ret;
  }
}
using namespace Graph;

char G[105][105];

int main() {
  int n, m, xs, ys, xt, yt;
  Graph::Init();
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; i ++) scanf("%s", G[i] + 1);
  for (int i = 1; i <= n; i ++)
    for (int j = 1; j <= m; j ++) {
      if (G[i][j] == 'S') {
	xs = i; ys = j;
	Graph::Add(S, i, INF, 0);
	Graph::Add(S, j + 100, INF, 0);
      }
      else if (G[i][j] == 'T') {
	xt = i; yt = j;
	Graph::Add(i, T, INF, 0);
	Graph::Add(j + 100, T, INF, 0);
      }
      else if (G[i][j] == 'o') {
	Graph::Add(i, j + 100, 1, 1);
      }
    }
  if (xs == xt || ys == yt) puts("-1");
  else printf("%d\n", Graph::MaxFlow());
  return 0;
}
