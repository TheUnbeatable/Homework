#include <cstdio>
#include <iostream>
#include <vector>
using namespace std;

typedef long long LL;
typedef pair <LL, LL> Pair;
typedef vector <Pair> vec;
const int N = 1.4e5 + 50;

int n, lc[N], rc[N], v[N];
vec dp[N], swp;
int sz[N];
LL lim;

template <typename T> inline void chkmin(T &x, T y) { if (x > y) x = y; }

inline void Init(int x) {
  if (!lc[x]) {
    sz[x] = 1;
    dp[x].emplace_back(v[x], v[x]);
    return;
  }
  Init(lc[x]); Init(rc[x]);
  sz[x] = min(sz[lc[x]], sz[rc[x]]) << 1;
  dp[x].reserve(sz[x]);
}

inline void Double(vec &a, int val) {
  swp.clear();
  for (vec :: iterator i = a.begin(), j = a.end(); i != a.end() || j != a.begin(); ) {
    if (i == a.end()) j --, swp.emplace_back(j -> second, j -> first);
    else if (j == a.begin()) swp.emplace_back(*i), i ++;
    else {
      if ((j - 1) -> second < i -> first) j --, swp.emplace_back(j -> second, j -> first);
      else swp.emplace_back(*i), i ++;
    }
  }
  a.clear();
  for (auto i : swp) {
    i.first += val; i.second += val;
    if (!a.size()) a.emplace_back(i);
    else {
      if ((a.end() - 1) -> first == i.first)
        chkmin((a.end() - 1) -> second, i.second);
      else if (i.second < (a.end() - 1) -> second)
        a.emplace_back(i);
    }
  }
}

inline void Upd(vec &a, vec &b, vec &c) {
  c.clear();
  if (!a.size() || !b.size()) return;
  for (vec :: iterator ia = a.begin(), ib = b.begin(); ia != a.end(); ia ++) {
    while (ib + 1 != b.end() && ia -> second + (ib + 1) -> first <= lim) ib ++;
    if (ia -> second + ib -> first <= lim) c.emplace_back(ia -> first, ib -> second);
  }
}

inline void Dfs(int x) {
  if (!lc[x]) return;
  Dfs(lc[x]); Dfs(rc[x]);
  Upd(dp[lc[x]], dp[rc[x]], dp[x]);
  Double(dp[x], v[x]);
}

int main() {
  scanf("%d", &n);
  for (int i = 2, f; i <= n; i ++) {
    scanf("%d%d", &f, &v[i]);
    if (!lc[f]) lc[f] = i;
    else rc[f] = i;
  }
  Init(1);
  swp.reserve(n << 1);
  LL L = 0, R = 1LL << 34, ans = 0;
  while (L <= R) {
    lim = (L + R) >> 1;
    Dfs(1);
    if (dp[1].size()) R = lim - 1, ans = lim;
    else L = lim + 1;
  }
  printf("%lld\n", ans);
  return 0;
}
