#include <cstdio>
#include <iostream>
#include <bitset>
using namespace std;

const int N = 404;
const int M = 1e5 + 50;

bitset <N> tur[N], res;
int x[M], y[M], n, m;
bool die[N];

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; i ++) tur[i][i] = 1;
  for (int i = 1; i <= m; i ++) scanf("%d%d", x + i, y + i);
  for (register int j = m, a, b; j; j --) {
    a = x[j]; b = y[j];
    for (register int i = 1; i <= n; i ++) {
      if (tur[i][a] && tur[i][b]) die[i] = 1;
      else if (tur[i][a] ^ tur[i][b]) tur[i][a] = tur[i][b] = 1;
    }
  }
  int cnt = 0;
  for (int i = 1; i <= n; i ++)
    if (!die[i])
      for (int j = i + 1; j <= n; j ++)
        if (!die[j]) {
          res = tur[i] & tur[j];
          if (!res.count()) cnt ++;
        }
  printf("%d\n", cnt);
  return 0;
}
