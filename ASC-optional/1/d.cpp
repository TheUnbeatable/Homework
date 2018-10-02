#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <bitset>
#include <vector>
using namespace std;

const int N = 1e4 + 5;

int n, m, out[N];
vector <int> eg[N];

int main() {
#ifdef ONLINE_JUDGE
  freopen("matrix.in", "r", stdin);
  freopen("matrix.out", "w", stdout);
#endif
  scanf("%d%d", &n, &m);
  for (int i = 1, u, v; i <= m; i ++) {
    scanf("%d%d", &u, &v);
    out[u] ++;
    eg[v].push_back(u);
    swap(u, v);
    out[u] ++;
    eg[v].push_back(u);
  }
  long long ans = 0;
  for (int i = 1; i <= n; i ++)
    for (auto j : eg[i]) ans += out[j];
  printf("%lld\n", ans);
  return 0;
}
