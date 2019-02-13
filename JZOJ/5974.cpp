#include <bits/stdc++.h>
using namespace std;

const int N = 5e4;

int mu[N], pri[N];
bool notp[N];

inline void Init() {
  int m = 0;
  mu[1] = 1;
  for (int i = 2; i < N; i ++) {
    if (!notp[i]) {
      pri[++ m] = i; mu[i] = -1;
    }
    for (int j = 1; j <= m; j ++) {
      if (pri[j] * i >= N) break;
      notp[pri[j] * i] = 1;
      mu[pri[j] * i] = - mu[i];
      if (i % pri[j] == 0) {
        mu[pri[j] * i] = 0; break;
      }
    }
  }
}

int n;
long long ans = 0;

inline long long calc(int n) {
  long long res = 0;
  for (int p = 1; p * p <= n; p ++) {
    int m = n / p, END = min(p + p - 1, m);
    for (int q = p + 1, nq; q <= END; q = nq + 1) {
      nq = min(END, m / (m / q));
      res += 1ll * (nq - q + 1) * (m / q);
    }
  }
  return res;
}

int main() {
  freopen("calc.in", "r", stdin);
  freopen("calc.out", "w", stdout);
  Init();
  scanf("%d", &n);
  int s = sqrt(n) + 1;
  for (int i = s, j = s; i > 0; i = j) {
    int smu = 0;
    for (; j > 0 && n / i / i == n / j / j; j --) smu += mu[j];
    ans += smu * calc(n / i / i);
  }
  printf("%lld\n", ans);
  return 0;
}
