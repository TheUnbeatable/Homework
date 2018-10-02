#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <map>
using namespace std;

typedef long long LL;
typedef pair <int, int> pii;

LL ans[40];

inline void Init() {
  map <pair <int , int> , LL>  cur, nxt;
  cur[pii(0, 1)] = 1;
  for (int i = 1; i <= 32; i ++) {
    for (auto it : cur) {
      ans[i] += it.second;
      int s = it.first.second, t = s & (- s), del = 0;
      for (int j = 0, lst = 0; j <= it.first.first + 1; j ++) {
        int na = it.first.first + ( (1 << j) > t ) - lst;
        int nb = ( (s ^ del) | (1 << j) ) >> lst;
        nxt[pii(na, nb)] += it.second;
        if ((s >> j) & 1) {
          lst = j; del |= 1 << j;
        }
      }
    }
    swap(cur, nxt);
    nxt.clear();
  }
}

int main() {
#ifdef ONLINE_JUDGE
  freopen("catalian.in", "r", stdin);
  freopen("catalian.out", "w", stdout);
#endif
  Init();
  for (int n, t = 1; ; t ++) {
    scanf("%d", &n);
    if (!n) break;
    printf("Case #%d: %lld\n", t, ans[n]);
  }
  return 0;
}
