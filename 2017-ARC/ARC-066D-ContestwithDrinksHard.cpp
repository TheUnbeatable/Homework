#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#define ri register int
using namespace std;

typedef long long LL;
const int N = 3e5 + 5;

int a[N], n, id[N];
LL L[N], R[N], A[N], B[N], g[N], sum[N], suf[N];

inline void DivideAndConquer(int l, int r, LL *L, LL *R, LL *dp) {
  if (l == r) {
    dp[l] = max(dp[l], L[l - 1] + R[l + 1] - a[l] + 1);
    return;
  }
  int mid = (l + r) >> 1;
  int top = 0;
  for (int i = l - 1; i < mid; i ++) {
    g[i] = L[i] + sum[i] + 1LL * i * (i - 1) / 2;
    while (top > 1 && (g[i] - g[id[top]]) * (id[top] - id[top - 1]) >= (g[id[top]] - g[id[top - 1]]) * (i - id[top])) top --;
    id[++ top] = i;
  }
  for (int i = mid; i <= r; i ++) {
    while (top > 1 && g[id[top]] - g[id[top - 1]] <= 1LL * i * (id[top] - id[top - 1])) top --;
    suf[i] = g[id[top]] - sum[i] + 1LL * i * (i + 1) / 2 - 1LL * id[top] * i + R[i + 1];
  }
  LL t = suf[r];
  dp[r] = max(dp[r], t);
  for (int i = r - 1; i >= mid; i --) {
    t = max(t, suf[i]);
    dp[i] = max(dp[i], t);
  }
  DivideAndConquer(l, mid, L, R, dp);
  DivideAndConquer(mid + 1, r, L, R, dp);
}

inline void DP(LL *dp) {
  int top = 1;
  LL S = 0;
  id[1] = 0;
  for (int i = 1; i <= n; i ++) {
    S += a[i];
    while (top > 1 && g[id[top]] - g[id[top - 1]] <= 1LL * i * (id[top] - id[top - 1])) top --;
    dp[i] = g[id[top]] - S + 1LL * i * (i + 1) / 2 - 1LL * id[top] * i;
    dp[i] = max(dp[i], dp[i - 1]);
    g[i] = dp[i] + S + 1LL * i * (i - 1) / 2;
    while (top > 1 && (g[i] - g[id[top]]) * (id[top] - id[top - 1]) >= (g[id[top]] - g[id[top - 1]]) * (i - id[top])) top --;
    id[++ top] = i;
  }
}

int main() {
  scanf("%d", &n);
  memset(A, - 0x3f, sizeof (LL) * (n + 2));
  memset(B, - 0x3f, sizeof (LL) * (n + 2));
  for (ri i = 1; i <= n; i ++) scanf("%d", &a[i]);
  DP(L); reverse(a + 1, a + n + 1);
  DP(R); reverse(R + 1, R + n + 1);
  reverse(a + 1, a + n + 1);
  for (ri i = 1; i <= n; i ++) sum[i] = sum[i - 1] + a[i];
  DivideAndConquer(1, n, L, R, A);
  for (ri i = (n >> 1); i; i --) {
    swap(L[i], L[n - i + 1]);
    swap(R[i], R[n - i + 1]);
    swap(a[i], a[n - i + 1]);
  }
  for (ri i = 1; i <= n; i ++) sum[i] = sum[i - 1] + a[i];
  DivideAndConquer(1, n, R, L, B);
  for (ri i = (n >> 1); i; i --) {
    swap(L[i], L[n - i + 1]);
    swap(R[i], R[n - i + 1]);
    swap(a[i], a[n - i + 1]);
    swap(B[i], B[n - i + 1]);
  }
  int m, p, v;
  scanf("%d", &m);
  for (; m; m --) {
    scanf("%d%d", &p, &v);
    printf("%lld\n", max(L[p - 1] + R[p + 1], max(A[p], B[p]) - v + a[p]));
  }
  return 0;
}
