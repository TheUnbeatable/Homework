#include <cstdio>
#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
using namespace std;

const int N = 2010;

vector <int> G[N], E[N];
int n, a[N];
bool vis[N], isrt[N];

inline void Dfs(int x) {
  vis[x] = 1;
  sort(G[x].begin(), G[x].end());
  for (auto i : G[x])
    if (!vis[i]) Dfs(i), E[x].push_back(i);
}

inline void Topo() {
  priority_queue <int> Q;
  for (int i = 1; i <= n; i ++)
    if (isrt[i]) Q.push(i);
  for (int i = 1, x; i <= n; i ++) {
    x = Q.top(); Q.pop();
    printf("%d ", a[x]);
    for (auto j : E[x]) Q.push(j);
  }
}

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i ++) scanf("%d", &a[i]);
  sort(a + 1, a + n + 1);
  for (int i = 1; i <= n; i ++)
    for (int j = i + 1; j <= n; j ++)
      if (__gcd(a[i], a[j]) > 1) {
        G[i].push_back(j);
        G[j].push_back(i);
      }
  for (int i = 1; i <= n; i ++)
    if (!vis[i]) Dfs(i), isrt[i] = 1;
  Topo();
  return 0;
}
