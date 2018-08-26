#include <cstdio>
#include <iostream>
#include <queue>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 53;
const int INF = 1e8;
const int S = N - 2, T = N - 1;

int n;

namespace Flow {
  int G[N][N], pos[N], dis[N];
  inline int Bfs() {
    queue <int> Q;
    memset(pos, 0, sizeof pos);
    memset(dis, -1, sizeof dis);
    Q.push(T); dis[T] = 0;
    while (!Q.empty()) {
      int x = Q.front(); Q.pop();
      for (int i = 0; i < N; i ++)
        if (G[i][x] && dis[i] == -1) {
          Q.push(i);
          dis[i] = dis[x] + 1;
        }
    }
    return dis[S];
  }
  inline int Dfs(int x, int flow) {
    if (x == T) return flow;
    int res = 0, tmp;
    for (int &i = pos[x]; i < N; i ++)
      if (G[x][i] && dis[i] == dis[x] - 1) {
        tmp = Dfs(i, min(flow, G[x][i]));
        res += tmp; flow -= tmp;
        G[x][i] -= tmp; G[i][x] += tmp;
        if (!flow) return res;
      }
    dis[x] = -1;
    return res;
  }
  inline int Maxflow() {
    int res = 0;
    while (Bfs() != -1) res += Dfs(S, INF);
    return res;
  }
}
using Flow :: G;

class OldBridges {
public:
  string isPossible(vector <string> bridges, int a1, int a2, int an, int b1, int b2, int bn) {
    n = bridges.size();
    memset(G, 0, sizeof G);
    for (int i = 0; i < n; i ++)
      for (int j = 0; j < n; j ++) {
        if (bridges[i][j] == 'X') G[i][j] = 0;
        else if (bridges[i][j] == 'O') G[i][j] = 2;
        else G[i][j] = INF;
      }
    G[S][a1] = G[a2][T] = an << 1;
    G[S][b1] = G[b2][T] = bn << 1;
    if (Flow :: Maxflow() < (an + bn) * 2) return "No";
    memset(G, 0, sizeof G);
    for (int i = 0; i < n; i ++)
      for (int j = 0; j < n; j ++) {
        if (bridges[i][j] == 'O') G[i][j] = 2;
        else if (bridges[i][j] == 'N') G[i][j] = INF;
      }
    G[S][a1] = G[a2][T] = an << 1;
    G[S][b2] = G[b1][T] = bn << 1;
    if (Flow :: Maxflow() < (an + bn) * 2) return "No";
    return "Yes";
  }
};
