#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;

typedef long long LL;
const int N = 2e5 + 50;
const int mod = 1e9 + 7;

struct Bit {
#define lb(x) (x & (- x))
  LL a[N];
  Bit() { memset(a, 0, sizeof a); }
  inline void Add(int p, LL v) {
    for (; p < N; p += lb(p)) {
      a[p] += v;
      if (a[p] >= mod) a[p] -= mod;
    }
  }
  inline LL Sum(int p) {
    LL res = 0;
    for (; p > 0; p -= lb(p)) {
      res += a[p];
      if (res >= mod) res -= mod;
    }
    return res;
  }
} dp;

int n, m;
int a[N], b[N], tab[N];
int x[N], y[N];
vector <int> po[N];
bool tops[N];

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; i ++) scanf("%d", &a[i]);
  for (int i = 1; i <= m; i ++) scanf("%d", &b[i]);
  int k = n; n = 0;
  for (int i = 1, p = 0; i <= k; i ++) {
    if (a[i] <= b[1] || a[i] >= b[m]) continue;
    while (p <= m && a[i] >= b[p + 1]) p ++;
    if (b[p] == a[i]) continue;
    n ++;
    x[n] = a[i] - b[p];
    y[n] = b[p + 1] - a[i];
  }
  for (int i = 1; i <= n; i ++) {
    tab[i + i - 1] = x[i];
    tab[i + i] = y[i];
  }
  sort(tab + 1, tab + n + n + 1);
  k = unique(tab + 1, tab + n + n + 1) - tab - 1;
  for (int i = 1, p, q; i <= n; i ++) {
    p = lower_bound(tab + 1, tab + k + 1, x[i]) - tab;
    q = lower_bound(tab + 1, tab + k + 1, y[i]) - tab;
    po[p].push_back(q);
  }
  for (int i = 1; i <= k; i ++) {
    vector <int> &v = po[i];
    sort(v.begin(), v.end());
    v.resize(unique(v.begin(), v.end()) - v.begin());
    reverse(v.begin(), v.end());
    for (auto it : v)
      dp.Add(it, dp.Sum(it - 1) + 1);
  }
  printf("%lld\n", dp.Sum(k) + 1);
  return 0;
}
