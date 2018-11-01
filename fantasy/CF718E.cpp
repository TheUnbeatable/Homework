#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <deque>
using namespace std;

const int N = 1e5 + 50;

struct edge {
  int nxt, to, len;
} e[N << 2];
int fir[N], cnt = 1;

inline void addedge(int x, int y, int w = 1) {
  e[++ cnt] = (edge) { fir[x], y, w }; fir[x] = cnt;
}

char s[N];
bool vis[N];
long long res[100];
int dis[N], num[1 << 11 | 5];
int n, tab[N], G[8][8], vec[N], t[N], id[N];

inline void Bfs(int c) {
  memset(vis, 0, sizeof vis);
  memset(dis, 0x3f, sizeof dis);
  deque <int> Q;
  for (int i = 1; i <= n; i ++)
    if (t[i] == c) {
      vis[i] = 1; Q.push_back(i); dis[i] = 0;
    }
  while (Q.size()) {
    int x = Q.front(); Q.pop_front();
    vis[x] = 1;
    for (int i = fir[x]; i; i = e[i].nxt)
      if (!vis[e[i].to] && dis[x] + e[i].len < dis[e[i].to]) {
        dis[e[i].to] = dis[x] + e[i].len;
        if (e[i].len == 0) {
          vis[e[i].to] = 1;
          Q.push_front(e[i].to);
        }
        else Q.push_back(e[i].to);
      }
  }
  for (int i = 1; i <= n; i ++)
    G[c][t[i]] = min(G[c][t[i]], dis[i]);
  for (int i = 1; i <= n; i ++)
    if (t[i] != c && dis[i] == G[c][t[i]] + 1)
      vec[i] |= 1 << c;
}

inline int calc(int x, int y) {
  int a = x >> 8, b = y >> 8;
  if (a == b) return 1;
  int res = 200;
  for (int i = 0; i < 8; i ++)
    if (i == a)
      res = min(res, ((y >> i) & 1) + G[b][i] + 1);
    else if (i == b)
      res = min(res, ((x >> i) & 1) + G[a][i] + 1);
    else
      res = min(res, ((x >> i) & 1) + G[a][i]
                + ((y >> i) & 1) + G[b][i] + 1);
  return res;
}

int main() {
  scanf("%d", &n);
  scanf("%s", s + 1);
  tab[0] = 1e5 + 1;
  for (int i = 1; i < 8; i ++)
    tab[i] = tab[i - 1] + 1;
  for (int i = 1; i <= n; i ++) {
    t[i] = s[i] - 'a';
    if (i > 1) {
      addedge(i - 1, i);
      addedge(i, i - 1);
    }
    addedge(i, tab[t[i]], 0);
    addedge(tab[t[i]], i);
  }
  memset(G, 0x3f, sizeof G);
  for (int i = 0; i < 8; i ++) Bfs(i);
  for (int i = 1; i <= n; i ++) {
    id[i] = (t[i] << 8) | vec[i];
    num[id[i]] ++;
  }
  for (int i = 0; i < (1 << 11); i ++)
    for (int j = 0; j < i; j ++)
      if (num[i] && num[j])
        res[calc(i, j)] += 1ll * num[i] * num[j];
  for (int i = 1; i <= n; i ++)
    for (int j = max(i - 20, 1); j < i; j ++) {
      int k = calc(id[i], id[j]);
      res[k] --;
      res[min(k, i - j)] ++;
    }
  for (int i = 50; i; i --)
    if (res[i] || i == 1) {
      if (i == 1) res[i] = 1ll * n * (n - 1) / 2;
      printf("%d %lld\n", i, res[i]);
      break;
    }
  return 0;
}
