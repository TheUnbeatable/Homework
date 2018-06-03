#include <cstdio>
#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

typedef long long LL;
const int N = 1e5 + 50;

struct NODE {
  int x, y, z;
} arr[N];

inline bool cmp(const NODE &p, const NODE &q) {
  return p.x - p.y > q.x - q.y;
}

int a, b, c, n;
LL tmp[N], ans, sum, Max = - 9e18;

int main() {
  scanf("%d%d%d", &a, &b, &c);
  n = a + b + c;
  for (int i = 1; i <= n; i ++)
    scanf("%d%d%d", &arr[i].x, &arr[i].y, &arr[i].z), ans += arr[i].z;
  sort(arr + 1, arr + n + 1, cmp);
  priority_queue <int, vector <int>, greater <int> > Q;
  for (int i = n; i; i --) {
    sum += arr[i].y - arr[i].z;
    Q.push(arr[i].y - arr[i].z);
    if ((int)Q.size() > b) {
      sum -= Q.top(); Q.pop();
    }
    tmp[i] = sum;
  }
  for (int i = 1; i <= b; i ++) Q.pop();
  sum = 0;
  for (int i = 1; i <= n; i ++) {
    sum += arr[i].x - arr[i].z;
    Q.push(arr[i].x - arr[i].z);
    if ((int)Q.size() > a) {
      sum -= Q.top(); Q.pop();
    }
    if (i >= a && n - i >= b) Max = max(Max, sum + tmp[i + 1]);
  }
  printf("%lld\n", ans + Max);
  return 0;
}
