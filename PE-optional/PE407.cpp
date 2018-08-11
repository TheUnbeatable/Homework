#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <bitset>
#include <vector>
using namespace std;

typedef long long LL;
const int N = 1e7;

int pri[2000000], m;
bitset <N> notp;
vector <int> rec[N + 10];

inline int calc(int x, int y) {
  int res = 1;
  while (y % x == 0) y /= x, res *= x;
  return res;
}

inline void Init() {
  notp[1] = 1;
  for (int i = 2; i <= N; i ++) {
    if (!notp[i]) {
      pri[++ m] = i;
      for (register int j = i; j <= N; j += i)
        rec[j].push_back(calc(i, j));
    }
    for (register int j = 1; j <= m; j ++) {
      int t = i * pri[j];
      if (t > N) break;
      notp[t] = 1;
      if (i % pri[j] == 0) break;
    }
  }
}

inline void exgcd(LL a, LL b, LL &x, LL &y) {
  if (!b) {
    x = 1; y = 0; return;
  }
  exgcd(b, a % b, x, y);
  LL t = x; x = y;
  y = t - a / b * y;
}

LL ans = 0, x, y, a, b;

int main() {
  Init();
  for (int i = 2; i <= N; i ++) {
    if (rec[i].size() == 1) {
      ans ++; continue;
    }
    LL M = 0;
    int k = rec[i].size();
    for (int j = 0; j < (1 << k); j += 2) {
      a = 1;
      for (register int w = 0; w < k; w ++)
        if ((j >> w) & 1) a *= rec[i][w];
      b = i / a;
      exgcd(a, b, x, y);
      if (x < 0) {
        x += (- x) / b * b;
        if (x < 0) x += b;
      }
      else {
        y += (- y) / a * a;
        if (y < 0) y += a;
      }
      M = max(M, a * x);
      M = max(M, b * y);
    }
    ans += M;
  }
  printf("%lld\n", ans);
  return 0;
}
