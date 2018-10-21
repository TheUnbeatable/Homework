#include <cstdio>
#include <iostream>
#include <algorithm>
#include <queue>
#define mp make_pair
using namespace std;

typedef pair <int, int> pii;
const int N = 1e5 + 5;

int n, tot = 0, r, c;
pii p[N];
bool ans = 1;

inline bool on_edge(int x, int y) {
  if (x == 0 || x == r || y == 0 || y == c) return true;
  return false;
}

inline int GetID(int x, int y) {
  if (x == 0) return r + c + r + c - y;
  if (x == r) return r + y;
  if (y == 0) return x;
  return r + c + r - x;
}

inline void solve() {
  sort(p + 1, p + tot + 1);
  priority_queue <int, vector <int>, greater <int> > Q;
  for (int i = 1; i <= tot && ans; i ++) {
    while (!Q.empty() && Q.top() <= p[i].first) Q.pop();
    if (!Q.empty() && Q.top() < p[i].second) ans = 0;
    Q.push(p[i].second);
  }
}

int main() {
  int x1, y1, x2, y2;
  scanf("%d%d%d", &r, &c, &n);
  for (int i = 1, a, b; i <= n; i ++) {
    scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
    if(!on_edge(x1, y1) || !on_edge(x2, y2)) continue;
    a = GetID(x1, y1); b = GetID(x2, y2);
    p[++ tot] = mp(min(a, b), max(a, b));
  }
  solve();
  printf("%s\n", ans ? "YES" : "NO");
  return 0;
}
