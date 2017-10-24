#include <cstdio>
#include <iostream>
#include <queue>
using namespace std;

typedef pair <int, int> pii;
typedef long long LL;
const int N = 2e5 + 5;

int n;
priority_queue <pii> tp;
priority_queue <int, vector <int>, greater <int> > le, del;

int main() {
  int D = 1e9, R = -1e9;
  scanf("%d", &n);
  for (int i = 1, x, y; i <= n; i ++) {
    scanf("%d%d", &x, &y);
    if (x > y) swap(x, y);
    tp.push(make_pair(y, x));
    le.push(x);
    R = max(R, x);
    D = min(D, y);
  }
  LL ans = 1LL * (R - le.top()) * (tp.top().first - D);
  pii cur;
  while (tp.top().first > tp.top().second) {
    cur = tp.top();
    tp.pop();
    del.push(cur.second);
    le.push(cur.first);
    tp.push(make_pair(cur.second, cur.first));
    D = min(D, cur.second);
    R = max(R, cur.first);
    while (!del.empty() && del.top() == le.top()) {
      del.pop(); le.pop();
    }
    ans = min(ans, 1LL * (R - le.top()) * (tp.top().first - D));
  }
  printf("%lld\n", ans);
  return 0;
}
