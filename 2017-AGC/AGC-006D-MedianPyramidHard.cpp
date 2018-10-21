#include <cstdio>
#include <iostream>
using namespace std;

typedef long long LL;
const int N = 1e5 + 5;

int a[N << 1], n;

inline bool judge(int x) {
  if (a[n] <= x && (a[n + 1] <= x || a[n - 1] <= x)) return 0;
  if (a[n] > x && (a[n + 1] > x || a[n - 1] > x)) return 1;
  int L = 0, R = 0;
  for (int i = n; i > 1; i --)
    if ((a[i] <= x) == (a[i - 1] <= x)) {L = i; break;}
  for (int i = n; i < (n << 1) - 1; i ++)
    if ((a[i] <= x) == (a[i + 1] <= x)) {R = i; break;}
  if (!L && !R) return a[1] > x;
  else if (L) {
    if (R) {
      if ((a[L] <= x) == (a[R] <= x)) return a[L] > x;
      if (n - L < R - n) return a[L] > x;
      else return a[R] > x;
    }
    else return a[L] > x;
  }
  else return a[R] > x;
}

int main() {
  scanf("%d", &n);
  for (int i = 1; i < (n << 1); i ++) scanf("%d", &a[i]);
  int l = 1, r = (n << 1) - 1, ans = 0, k, mid;
  while (l <= r) {
    mid = (l + r) >> 1;
    k = judge(mid);
    if (!k) ans = mid, r = mid - 1;
    else l = mid + 1;
  }
  printf("%d\n", ans);
  return 0;
}
