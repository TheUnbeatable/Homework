#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 10;

double f[N], g[N], d[N];
int n, m, fa[N], ga[N], R;
vector <pair <int, int> > id[N];

inline int getf(int x) {
  return fa[x] == x ? x : fa[x] = getf(fa[x]);
}

inline int getg(int x) {
  return ga[x] == x ? x : ga[x] = getg(ga[x]);
}


inline void mer(int a, int b) {
  if (a < 0) return;
  fa[a] = b; ga[b] = a; d[b] += d[a];
  if (d[b] >= 0) mer(getg(b) - 1, b);
}

inline pair <int, int> calc(double lambda) {
  for (int i = 0; i <= R; i ++) fa[i] = ga[i] = i;
  f[0] = g[0] = 0;
  double val = 0;
  d[0] = 0;
  for (int i = 1; i <= R; i ++) {
    for (auto j : id[i]) {
      int k = getf(j.first - 1);
      d[k] += j.second;
      val += j.second;
      if (d[k] >= 0) mer(getg(k) - 1, k);
    }
    if (d[getf(0)] - lambda >= f[i - 1]) {
      f[i] = d[getf(0)] - lambda;
      g[i] = g[getf(0)] + 1;
    } else {
      f[i] = f[i - 1]; g[i] = g[i - 1];
    }
    d[i] = f[i] - val;
    if (d[i] >= 0) mer(i - 1, i);
    val = f[i];
  }
  return make_pair(g[R], f[R]);
}

int main() {
  freopen("party.in", "r", stdin);
  freopen("party.out", "w", stdout);
  scanf("%d%d", &n, &m);
  for (int i = 1, l, r, c; i <= n; i ++) {
    scanf("%d%d%d", &l, &r, &c);
    id[r - 1].push_back(make_pair(l, c));
    R = max(R, r - 1);
  }
  int L = 0, R = 1e9, mid, best = 0;
  while (L <= R) {
    mid = (L + R) >> 1;
    pair <int, int> val = calc(mid);
    if (val.first > m) L = mid + 1;
    else best = mid, R = mid - 1;
  }
  pair <int, int> val = calc(best);
  pair <int, int> val1 = calc(best - 1e-6);
  if (val1.first != val.first) best = val.second + m * best;
  else best = calc(best - 1).second + m * (best - 1);
  printf("%d\n", best);
  return 0;
}
