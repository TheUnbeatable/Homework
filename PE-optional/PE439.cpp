#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <bitset>
#include <unordered_map>
using namespace std;

typedef long long LL;
const int N = 3e7;
const LL mod = 1e9;
const LL sqr = mod * mod;

unordered_map <LL, LL> rec;

bitset <N> notp;
int pri[N / 4], m, mu[N];

inline void Init() {
  for (int i = 2; i < N; i ++) {
    if (!notp[i]) {
      pri[++ m] = i; mu[i] = - 1;
    }
    for (int j = 1; j <= m; j ++) {
      int t = pri[j] * i;
      if (t >= N) break;
      notp[t] = 1;
      if (i % pri[j] == 0) {
        mu[t] = 0; break;
      }
      mu[t] = - mu[i];
    }
  }
  mu[1] = 1;
  for (int i = 2; i < N; i ++) {
    mu[i] = mu[i - 1] + 1ll * mu[i] * i;
    if (mu[i] < 0) mu[i] += mod;
    if (mu[i] >= mod) mu[i] -= mod;
  }
}

inline LL calc(LL i, LL j) {
  if (i >= mod) i %= mod;
  if (j >= mod) j %= mod;
  LL res = ((i + j) * (j - i + 1)) % mod;
  return (res < 0 ? res + mod : res);
}

inline LL Sum(LL n) {
  if (n < N) return mu[n];
  if (rec.count(n)) return rec[n];
  LL res = 0;
  for (LL i = 2, j; i <= n; i = j + 1) {
    j = n / (n / i);
    res -= Sum(n / i) * calc(i, j);
    if (res < 0) res += sqr;
  }
  res %= mod;
  res /= 2;
  res ++;
  return rec[n] = (res < 0 ? res + mod : res);
}

inline LL Calc(LL n) {
  LL res = 0;
  for (LL i = 1, j; i <= n; i = j + 1) {
    j = n / (n / i);
    res += (n / i) % mod * calc(i, j);
    if (res >= sqr) res -= sqr;
  }
  res /= 2;
  res %= mod;
  return (res < 0 ? res + mod : res);
}

LL n = 1e11;

int main() {
  Init();
  LL ans = 0, lst = 0, cur;
  for (LL i = 1, j, t; i <= n; i = j + 1) {
    j = n / (n / i);
    t = Calc(n / i);
    cur = Sum(j);
    (ans += (cur - lst) * t % mod * t) %= mod;
    lst = cur;
  }
  ans %= mod;
  printf("%lld\n", ans < 0 ? ans + mod : ans);
  return 0;
}
