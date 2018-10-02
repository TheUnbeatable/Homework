#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

typedef long long LL;
const int N = 2e5 + 50;
const LL mod = 1e9 + 7;

int n, tab[N];
pair <int, int> a[N], b[N];
LL mul[N << 2], sum[N << 2];

inline void Down(int x) {
  if (mul[x] > 1) {
    (mul[x << 1] *= mul[x]) %= mod;
    (sum[x << 1] *= mul[x]) %= mod;
    (mul[x << 1 | 1] *= mul[x]) %= mod;
    (sum[x << 1 | 1] *= mul[x]) %= mod;
    mul[x] = 1;
  }
}

#define mid ((L + R) >> 1)

inline void Add(int p, LL val, int x = 1, int L = 0, int R = n) {
  if (L == R) {
    sum[x] += val;
    if (sum[x] >= mod) sum[x] -= mod;
    return;
  }
  Down(x);
  if (p <= mid) Add(p, val, x << 1, L, mid);
  else Add(p, val, x << 1 | 1, mid + 1, R);
  sum[x] = sum[x << 1] + sum[x << 1 | 1];
  if (sum[x] >= mod) sum[x] -= mod;
}

inline LL Sum(int l, int r, int x = 1, int L = 0, int R = n) {
  if (l == L && R == r) return sum[x];
  Down(x);
  if (r <= mid) return Sum(l, r, x << 1, L, mid);
  else if (l > mid) return Sum(l, r, x << 1 | 1, mid + 1, R);
  else return ( Sum(l, mid, x << 1, L, mid) + Sum(mid + 1, r, x << 1 | 1, mid + 1, R) ) % mod;
}

inline void Double(int l, int r, int x = 1, int L = 0, int R = n) {
  if (l <= L && R <= r) {
    (sum[x] <<= 1) %= mod;
    (mul[x] <<= 1) %= mod;
    return;
  }
  Down(x);
  if (l <= mid) Double(l, r, x << 1, L, mid);
  if (r > mid) Double(l, r, x << 1 | 1, mid + 1, R);
  sum[x] = sum[x << 1] + sum[x << 1 | 1];
  if (sum[x] >= mod) sum[x] -= mod;
}

#undef mid

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i ++) {
    scanf("%d%d", &a[i].first, &a[i].second);
    tab[i] = a[i].second;
  }
  for (int i = 1; i < (N << 2); i ++) mul[i] = 1;
  sort(a + 1, a + n + 1);
  sort(tab + 1, tab + n + 1);
  for (int i = 1; i <= n; i ++)
    b[i].second = max(b[i - 1].second, a[i].second);
  b[n + 1].first = 1e9;
  for (int i = n; i; i --)
    b[i].first = min(b[i + 1].first, a[i].second);
  sort(b + 1, b + n + 1);
  Add(0, 1);
  for (int i = 1, l, r; i <= n; i ++) {
    l = lower_bound(tab + 1, tab + n + 1, b[i].first) - tab;
    r = upper_bound(tab + 1, tab + n + 1, b[i].second) - tab - 1;
    LL val = Sum(l - 1, r - 1);
    Double(r, n);
    Add(r, val);
  }
  printf("%lld\n", Sum(n, n));
  return 0;
}
