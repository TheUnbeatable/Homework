#include <bits/stdc++.h>
using namespace std;

typedef vector <int> vi;
const int N = 305;

class TreePuzzle {
private:
  int G[N][N], deg[N];
  vector <int> pos[N];
  inline bool samedir(int x, int y, int z) {
    return G[x][z] == G[x][y] + G[y][z];
  }
public:
  inline vi reachable(vi parent, vi token) {
    int n = parent.size();
    memset(G, 0x3f, sizeof G);
    memset(deg, 0, sizeof deg);
    for (int i = 0; i < n; i ++) {
      G[i][i] = 0;
      if (i) {
        deg[i] ++; deg[parent[i]] ++;
        G[i][parent[i]] = G[parent[i]][i] = 1;
      }
    }
    for (int k = 0; k < n; k ++)
      for (int i = 0; i < n; i ++)
        for (int j = 0; j < n; j ++)
          G[i][j] = min(G[i][j], G[i][k] + G[k][j]);
    vector <int> can(n);
    can[0] = 1;
    pos[0] = token;
    int empty = 0;
    for (int i = 0; i < n; i ++) empty += !token[i];
    for (int y = 1, x; y < n; y ++) {
      x = parent[y];
      if (!can[x]) continue;
      vi &mp = pos[y];
      // move directly
      mp = pos[x];
      int r = -1;
      for (int i = 0; i < n; i ++)
        if (samedir(x, y, i) && !mp[i]) {
          if (r == -1) r = i;
          else if (G[x][i] < G[x][r]) r = i;
        }
      if (~ r) {
        mp[r] = 1; mp[x] = 0; can[y] = 1;
        continue;
      }
      // two empty neighbors
      for (int i = 0; i < n; i ++)
        if (G[i][x] == 1 && i != y) {
          for (int j = 0; j < n; j ++)
            if (samedir(x, i, j) && !mp[j]) {
              if (~ r) {
                mp[j] = 1; mp[x] = 0; can[y] = 1;
              }
              else r = i;
              break;
            }
          if (can[y]) break;
        }
      if (can[y]) continue;
      if (r == -1) continue;
      int s = -1;
      for (int i = 0; i < n; i ++)
        if (samedir(x, r, i) && deg[i] >= 3) {
          if (s == -1) s = i;
          else if (G[x][i] < G[x][s]) s = i;
        }
      if (s == -1) continue;
      if (G[x][s] + 2 > empty) continue;
      can[y] = 1;
      mp[x] = 0;
      for (int i = 0; i < n; i ++)
        if (samedir(x, r, i) && !mp[i]) {
          mp[i] = 1; break;
        }
    }
    return can;
  }
};
