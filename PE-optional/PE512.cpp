#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <map>
using namespace std;

typedef long long LL;
const int N = 1e7;

bool notp[N];
int phi[N], pri[N], m;
LL sum[N];
map <int, LL> rec;

inline void Init() {
  sum[1] = phi[1] = 1;
  for (int i = 2; i < N; i ++) {
    if (!notp[i]) {
      pri[++ m] = i;
      phi[i] = i - 1;
    }
    for (int j = 1; j <= m; j ++) {
      int t = i * pri[j];
      if (t >= N) break;
      notp[t] = 1;
      if (i % pri[j] == 0) {
        phi[t] = phi[i] * pri[j];
        break;
      }
      phi[t] = phi[i] * (pri[j] - 1);
    }
    sum[i] = sum[i - 1] + phi[i];
  }
}

inline LL calc(int n) {
  if (n < N) return sum[n];
  if (rec.count(n)) return rec[n];
  LL s = 1ll * n * (n + 1) / 2;
  for (int i = 2, j; i <= n; i = j + 1) {
    j = n / (n / i); j = min(j, n);
    s -= (j - i + 1) * calc(n / i);
  }
  return rec[n] = s;
}

int n = 5e8;

int main() {
  Init();
  LL ans = calc(n);
  for (n >>= 1; n; n >>= 1) ans -= calc(n);
  printf("%lld\n", ans);
  return 0;
}
