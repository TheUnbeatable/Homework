#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;

typedef long long LL;
const int V = 2e5 + 5;
const int N = 1e6;
const LL mod = 924844033;
const LL g = 5;

struct edge {
  int nxt, to;
} e[V << 1];
LL fac[N], inv[N], a[N], b[N], c[N];
int pos[N], fir[V], sz[V], cnt = 0, n;

inline void addedge(int x, int y) {
  e[++ cnt] = (edge) { fir[x], y  };
  fir[x] = cnt;
}

inline LL pow(LL x, LL exp) {
  LL r = 1; x %= mod;
  exp = (exp + mod - 1) % (mod - 1);
  for (; exp; exp >>= 1, x = x * x % mod)
    if (exp & 1) r = r * x % mod;
  return r;
}

inline void pre(int n) {
  int t = n >> 1;
  for (int i = fac[0] = 1; i < n; i ++) {
    fac[i] = fac[i - 1] * i % mod;
    pos[i] = (pos[i >> 1] >> 1) ^ (t * (i & 1));
  }
  a[n - 1] = inv[n - 1] = pow(fac[n - 1], mod - 2);
  for (int i = n - 1; i; i --) a[i - 1] = inv[i - 1] = inv[i] * i % mod;
}

inline void dfs(int x, int fa) {
  sz[x] = 1;
  for (int i = fir[x]; i; i = e[i].nxt)
    if (e[i].to != fa) {
      dfs(e[i].to, x);
      sz[x] += sz[e[i].to];
      b[sz[e[i].to]] --;
    }
  if (x != 1) b[n - sz[x]] --;
}

inline void NTT(LL *a, int n, LL t) {
  for (int i = 0; i < n; i ++)
    if (pos[i] < i) swap(a[pos[i]], a[i]);
  LL x, y, per, cur;
  for (int i = 2, ii = 1; i <= n; i <<= 1, ii <<= 1) {
    per = pow(g, t * (mod - 1) / i);
    for (int j = 0; j < n; j += i) {
      cur = 1;
      for (int k = j; k < j + ii; k ++) {
        x = a[k];
        y = cur * a[k + ii] % mod;
        a[k] = x + y;
        if (a[k] >= mod) a[k] -= mod;
        a[k + ii] = x - y;
        if (a[k + ii] < 0) a[k + ii] += mod;
        cur = cur * per % mod;
      }
    }
  }
  if (t == -1) {
    LL I = pow((LL)n, mod - 2);
    for (int i = 0; i < n; i ++) a[i] = a[i] * I % mod;
  }
}

int main() {
  scanf("%d", &n);
  for (int i = 1, x, y; i < n; i ++) {
    scanf("%d%d", &x, &y);
    addedge(x, y); addedge(y, x);
  }
  int k = 1;
  for (; k <= n; k <<= 1);
  k <<= 1;
  pre(k);
  dfs(1, 0); b[n] = n;
  for (int i = 0; i < k; i ++) {
    b[i] = b[i] * fac[i] % mod;
    if (b[i] < 0) b[i] += mod;
  }
  reverse(b, b + n + 1); b[n] = 0;
  for (int i = n + 1; i <= k; i ++) a[i] = b[i] = 0;
  NTT(a, k, 1);
  NTT(b, k, 1);
  for (int i = 0; i < k; i ++) a[i] = a[i] * b[i] % mod;
  NTT(a, k, -1);
  for (int i = n - 1; i >= 0; i --)
    printf("%lld\n", a[i] * inv[n - i] % mod);
  return 0;
}
