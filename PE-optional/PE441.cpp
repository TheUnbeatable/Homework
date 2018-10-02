#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <bitset>
using namespace std;

typedef long long LL;
const int N = 1e7 + 10;

bitset <N> notp;
int mu[N], pri[N], m;
double pre[N];
int n = 1e7;

inline void Init() {
  mu[1] = 1;
  for (int i = 2; i <= n; i ++) {
    if (!notp[i]) {
      pri[++ m] = i; mu[i] = -1;
    }
    for (int j = 1; j <= m; j ++) {
      int t = i * pri[j];
      if (t > n) break;
      notp[t] = 1;
      if (i % pri[j] == 0) {
        mu[t] = 0; break;
      }
      mu[t] = - mu[i];
    }
  }
  for (int i = 1; i <= n; i ++)
    pre[i] = pre[i - 1] + 1.0 / i;
}

int main() {
  Init();
  double ans = 0;
  for (int d = 1; d <= n; d ++) {
    if (!mu[d]) continue;
    int t = n / d, lb;
    double sum = 0;
    for (register int i = 1; i < t; i ++) {
      if (t - i >= i)
        sum += ( pre[t - i] - pre[i] ) * ( d + 1.0 / i );
      lb = max(i + 1, t - i + 1);
      sum += ( ( pre[t] - pre[lb - 1] ) * (n + 1) - d * ( t - lb + 1 ) ) * (1.0 / i);
    }
    ans += sum * mu[d] / d / d;
  }
  printf("%.5lf\n", ans);
  return 0;
}
