#include <cstdio>
#include <iostream>
#include <cstring>
#include <queue>
#include <set>
#define travel(x, i) for (int i = fir[x]; i; i = e[i].nxt)
using namespace std;

const int N = 2e5 + 5;

struct edge {
  int nxt, to;
} e[N];
int fir[N], cnt = 0;
int deg[N], sg[N], cyc[N], tot = 0, Sg[N];
bool tab[N];
queue <int> Q;
set <int> O[N];

inline void add(int x, int y) {
  deg[y] ++;
  e[++ cnt] = (edge){fir[x], y};
  fir[x] = cnt;
}

inline int mex(const set <int> &fut) {
  if (fut.size() == 0) return 0;
  int t = 0;
  for (set <int> :: iterator it = fut.begin(); it != fut.end(); it ++, t ++)
    if ((*it) != t) return t;
  return t;
}

inline bool check(int x) {
  set <int> tmp;
  Sg[1] = x;
  for (int i = 2; i <= tot; i ++) {
    tmp = O[cyc[i]];
    tmp.insert(Sg[i - 1]);
    Sg[i] = mex(tmp);
  }
  tmp = O[cyc[1]];
  tmp.insert(Sg[tot]);
  if (mex(tmp) == x) return true;
  return false;
}

int main() {
  int n, x;
  scanf("%d", &n);
  for (int i = 1; i <= n; i ++) {
    scanf("%d", &x);
    add(i, x);
  }
  memset(sg, -1, sizeof sg);
  for (int i = 1; i <= n; i ++)
    if (!deg[i]) Q.push(i), sg[i] = 0;
  while (!Q.empty()) {
    x = Q.front();
    Q.pop();
    travel(x, i) {
      deg[e[i].to] --;
      O[e[i].to].insert(sg[x]);
      if (!deg[e[i].to]) {
	sg[e[i].to] = mex(O[e[i].to]);
	Q.push(e[i].to);
      }
    }
  }
  int p = 0;
  for (int i = 1; i <= n; i ++)
    if (deg[i]) {p = i; break;}
  if (!p) return !puts("POSSIBLE");
  bool st = 1;
  for (int i = p; st || i != p; st = 0) {
    cyc[++ tot] = i;
    travel(i, j)
      if (deg[e[j].to]) {
	i = e[j].to;
	break;
      }
  }
  set <int> tmp = O[p];
  x = mex(tmp);
  if (check(x)) return !puts("POSSIBLE");
  tmp.insert(x);
  x = mex(tmp);
  if (check(x)) return !puts("POSSIBLE");
  puts("IMPOSSIBLE");
  return 0;
}
