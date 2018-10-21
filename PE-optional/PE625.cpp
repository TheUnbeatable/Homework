#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <bitset>
#include <unordered_map>
using namespace std;

typedef long long LL;
const int N = 2e7;
const LL mod = 998244353;
const LL sqr = mod * mod;
const LL INV2 = (mod + 1) >> 1;

bitset <N> notp;
int pri[N / 5], m;
LL phi[N], sum[N];
unordered_map <LL, LL> rec;

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
    sum[i] %= mod;
  }
}

inline LL sumup(LL x, LL y) {
  return (y - x + 1) % mod * ( (x + y) % mod ) % mod * INV2 % mod;
}

inline LL calc(LL n) {
  if (n < N) return sum[n];
  if (rec.count(n)) return rec[n];
  LL s = sumup(1, n);
  for (LL i = 2, j; i <= n; i = j + 1) {
    j = n / (n / i);
    s -= (j - i + 1) % mod * calc(n / i);
    if (s < 0) s += sqr;
  }
  return rec[n] = s % mod;
}

LL n = 1e11, ans;

int main() {
  Init();
  for (LL i = 1, j; i <= n; i = j + 1) {
    j = n / (n / i);
    ans += sumup(i, j) * calc(n / i);
    if (ans >= sqr) ans -= sqr;
  }
  ans %= mod;
  printf("%lld\n", ans);
  return 0;
}
