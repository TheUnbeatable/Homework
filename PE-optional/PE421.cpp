#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
const int N = 1e8 + 50;
const int M = 5861455;

const LL n = 1e11;
const int m = 1e8;

inline int Pow(int x, int e, int mod) {
  LL res = 1;
  for (; e; e >>= 1, x = (LL)x * x % mod)
    if (e & 1) res = res * x % mod;
  return res;
}

bitset <N> notp;
int pri[M], cnt;
int id[N];
vector <int> d[M];

inline void sieve() {
  for (int i = 2; i <= m; i ++) {
    if (!notp[i]) {
      pri[++ cnt] = i;
      id[i] = cnt;
    }
    for (int j = 1, k; j <= cnt; j ++) {
      k = i * pri[j];
      if (k > m) break;
      notp[k] = 1;
      if (i % pri[j] == 0) break;
    }
  }
  for (int i = 1; i <= cnt; i ++) d[i].reserve(5);
  for (int i = 1, p; i <= cnt; i ++) {
    p = pri[i];
    for (int j = p; j < m; j += p)
      if (!notp[j + 1]) d[id[j + 1]].push_back(p);
  }
}

inline int calc(vector <int> &d, int p) {
  for (auto &i : d) i = (p - 1) / i;
  for (int i = 2; i < p; i ++) {
    bool ok = 1;
    for (size_t j = 0; ok && j < d.size(); j ++)
      if (Pow(i, d[j], p) == 1) ok = 0;
    if (ok) return i;
  }
  throw;
}

int main() {
  sieve();
  LL ans = ((n - 1) / 2 + 1) * 2;
  for (int i = 2, e; i <= cnt; i ++) {
    int p = pri[i], g = calc(d[i], p);
    LL cnt = 0;
    for (int t = 1; t < 30; t += 2)
      if (t * (p - 1) % 30 == 0) {
        e = Pow(g, t * (p - 1) / 30, p);
        cnt += (n - e) / p + 1;
      }
    ans += cnt * p;
  }
  printf("%lld\n", ans);
  return 0;
}
