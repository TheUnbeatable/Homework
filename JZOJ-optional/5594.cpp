#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long LL;
const int N = 2e5;

LL L, R;
LL val[N], f[N];
int pri[N], m;
bool notp[N];

inline void init() {
  for (int i = 2; i < N; i ++)
    if (!notp[i]) {
      pri[++ m] = i;
      for (int j = i; j < N; j += i) notp[j] = 1;
    }
}

inline LL sum(LL x) {
  return (x & 1) ? (x + 1) / 2 * x : x / 2 * (x + 1);
}

LL t, n;

inline int pos(LL x) { return x <= t ? x : t + t - n / x; }

inline LL solve(LL _n) {
  n = _n;
  t = sqrt(n) + 2;
  memset(val, 0, sizeof val);
  for (LL i = 1, j; i <= n; i = j + 1) {
    j = n / (n / i); val[pos(j)] = j; f[pos(j)] = sum(j) - 1;
  }
  LL sum = 0, ans = 0;
  for (int i = 1, j = 1; (LL) pri[i] * pri[i] <= n; i ++) {
    LL p = pri[i];
    while (val[j] < p * p) j ++;
    ans += f[pos(n / p)] - sum;
    for (int k = t + t; k >= j; k --) f[k] -= (f[pos(val[k] / p)] - sum) * p;
    sum += p;
  }
  return ans;
}

int main() {
  freopen("factor.in", "r", stdin);
  freopen("factor.out", "w", stdout);
  init();
  scanf("%llu%llu", &L, &R);
  printf("%llu\n", solve(R) - solve(L - 1));
  return 0;
}
