#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
const int N = 2e5 + 50;
const int mod = 1e9 + 7;
const int I2 = (mod + 1) / 2;

int n;
pair <int, int> a[N];

inline LL Pow(LL x, LL exp) {
  LL res = 1;
  for (; exp; exp >>= 1, x = x * x % mod)
    if (exp & 1) res = res * x % mod;
  return res;
}

LL tag[N << 2], sum[N << 2], mono[N << 2];

inline void tagdown(int x) {
  if (tag[x] != 1) {
    (tag[x << 1] *= tag[x]) %= mod;
    (sum[x << 1] *= tag[x]) %= mod;
    (tag[x << 1 | 1] *= tag[x]) %= mod;
    (sum[x << 1 | 1] *= tag[x]) %= mod;
    tag[x] = 1;
  }
}

#define mid ((L + R) >> 1)

inline void Set(int p, int v, int x = 1, int L = 1, int R = n) {
  if (L == R) {
    mono[x] = 1; sum[x] = v; return;
  }
  tagdown(x);
  if (p <= mid) Set(p, v, x << 1, L, mid);
  else Set(p, v, x << 1 | 1, mid + 1, R);
  sum[x] = sum[x << 1] + sum[x << 1 | 1];
  sum[x] >= mod ? sum[x] -= mod : 0;
  mono[x] ++;
}

inline void Add(pair <LL, int> &a, pair <LL, int> b) {
  a.first += b.first; a.second += b.second;
}

inline pair <LL, int> Sum(int l, int r, int x = 1, int L = 1, int R = n) {
  if (l <= L && R <= r) return make_pair(sum[x], mono[x]);
  tagdown(x);
  pair <LL, int> res;
  if (l <= mid) res = Sum(l, r, x << 1, L, mid);
  if (r > mid) Add(res, Sum(l, r, x << 1 | 1, mid + 1, R));
  return res;
}

inline void Mul(LL val) {
  tag[1] = tag[1] * val % mod;
  sum[1] = sum[1] * val % mod;
}

LL pre[N];

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i ++) {
    scanf("%d", &a[i].first); a[i].second = i;
  }
  sort(a + 1, a + n + 1);
  LL ans = 0;
  for (int i = pre[0] = 1; i <= n; i ++)
    pre[i] = pre[i - 1] * (a[i].first - i + 1) % mod;
  if (!pre[n]) {
    puts("0"); return 0;
  }
  for (int i = 0; i < (N << 2); i ++) tag[i] = 1;
  LL suf = 1;
  for (int i = n; i; i --) {
    pair <LL, int> tmp = Sum(a[i].second, n);
    tmp.first %= mod;
    LL fix = (a[i].first - i) * pre[i] % mod * I2 % mod;
    ans += tmp.first * fix % mod;
    ans -= (sum[1] - tmp.first) * fix % mod;
    ans += (mono[1] - tmp.second) * pre[n] % mod;
    Mul(a[i].first - i);
    Set(a[i].second, suf);
    suf = suf * (a[i].first - i + 1) % mod;
  }
  ans = (ans % mod + mod) % mod;
  printf("%lld\n", ans);
  return 0;
}
