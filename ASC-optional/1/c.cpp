#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;

const int N = 5e5 + 50;

int n;
int son[N], f[N];
bool chos[N], vis[N];

inline void Match() {
  queue <int> Q;
  int cnt = 0;
  for (int i = 1; i <= n; i ++)
    if (!son[i]) Q.push(i);
  for (int i = 1, x; i < n; i ++) {
    x = Q.front(); Q.pop();
    if (!vis[x] && !vis[f[x]])
      chos[x] = vis[f[x]] = vis[x] = 1, cnt ++;
    son[f[x]] --;
    if (!son[f[x]]) Q.push(f[x]);
  }
  printf("%lld\n", cnt * 1000ll);
  for (int i = 2; i <= n; i ++)
    if (chos[i]) printf("%d ", i);
  puts("");
}

int main() {
#ifdef ONLINE_JUDGE
  freopen("grant.in", "r", stdin);
  freopen("grant.out", "w", stdout);
#endif
  scanf("%d", &n);
  for (int i = 2; i <= n; i ++)
    scanf("%d", &f[i]), son[f[i]] ++;
  Match();
  return 0;
}
