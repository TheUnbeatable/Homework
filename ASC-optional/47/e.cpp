#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <set>
#include <cstdlib>
using namespace std;

typedef long long LL;
const int N = 36;

LL a[3][N][N];
int n, id[3][N];

inline LL calc(int i, int j) {
  return a[0][id[0][i]][j] * a[1][id[1][i]][j] * a[2][id[2][i]][j];
}

inline bool judge() {
  set <int> vis;
  for (int i = 1; i <= n; i ++)
    for (int j = 1; j <= n; j ++) {
      if ( vis.count( calc(i, j) ) ) return 0;
      vis.insert( calc(i, j) );
    }
  return 1;
}

int main() {
#ifdef ONLINE_JUDGE
  freopen("elegant.in", "r", stdin);
  freopen("elegant.out", "w", stdout);
#endif
  srand(123456);
  scanf("%d", &n);
  int cur = 2;
  for (int k = 0; k < 3; k ++) {
    for (int t = 1; t <= n; t ++, cur ++) {
      for (; cur; cur ++) {
        bool ok = 1;
        for (int i = 2; i * i <= cur; i ++)
          if (cur % i == 0) { ok = 0; break; }
        if (ok) break;
      }
      a[k][1][t] = cur;
    }
    for (int i = 2; i <= n; i ++)
      for (int j = 1; j <= n; j ++)
        a[k][i][j] = a[k][i - 1][j == n ? 1 : j + 1];
  }
  for (int i = 1; i <= n; i ++)
    id[0][i] = id[1][i] = id[2][i] = i;
  while (!judge()) {
    for (int i = 0; i < 3; i ++)
      random_shuffle(id[i] + 1, id[i] + n + 1);
  }
  for (int i = 1; i <= n; i ++) {
    for (int j = 1; j <= n; j ++)
      printf("%lld ", calc(i, j));
    puts("");
  }
  return 0;
}
