#pragma GCC optimize(3)
#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

typedef long long LL;
const int N = 4e5 + 50;
const int sgn[2] = { 1, -1 };
const LL INF = 1e16;

int n, a[N];

namespace Seg {
#define mid ((L + R) >> 1)
#define lc (x << 1)
#define rc (x << 1 | 1)
  /*
  ** segment tree which supports:
  ** 1. finding the maximum value of f[l,r] = 2 * sum(l + 1,r - 1) + a[l] + a[r]
  ** 2. deleting a[p] by setting its size as 0
  ** 3. for i in range [l,r] set a[i] to -a[i]
  ** details
  ** 1. determine whether a number exists through siz[N]
  ** 2. when a segment no longer contain numbers, its pref && suf && ans should be set to INF
  */
  struct Mono {
    LL x; int p;
    Mono() {}
    Mono(LL _x, int _p = 0): x(_x), p(_p) {}
    inline bool operator < (const Mono &o) const { return x < o.x; }
    inline Mono operator + (const LL o) { return Mono(x + o, p); }
    inline Mono operator - (const LL o) { return Mono(x - o, p); }
  } pre[N], ipre[N], suf[N], isuf[N];
  struct Doub {
    LL x; int l, r;
    Doub() {}
    Doub(LL _x, int _l = 0, int _r = 0): x(_x), l(_l), r(_r) {}
    inline bool operator < (const Doub &o) const { return x < o.x; }
  } ans[N], ians[N];
  int siz[N];
  LL sum[N];
  bool rev[N];
  inline void REV(int x) {
    if (!siz[x]) return;
    rev[x] ^= 1;
    swap(pre[x], ipre[x]);
    swap(suf[x], isuf[x]);
    swap(ans[x], ians[x]);
    sum[x] = - sum[x];
  }
  inline void DOWN(int x) {
    if (!rev[x]) return;
    rev[x] = 0; REV(lc); REV(rc);
  }
  inline void UPD(int x) {
    DOWN(x);
    siz[x] = siz[lc] + siz[rc];
    sum[x] = sum[lc] + sum[rc];
    if (!siz[x]) {
      pre[x] = suf[x] = ipre[x] = isuf[x] = INF;
      ans[x] = ians[x] = INF;
      return;
    }
    pre[x] = min(pre[lc], pre[rc] + (sum[lc] << 1));
    suf[x] = min(suf[rc], suf[lc] + (sum[rc] << 1));
    ipre[x] = min(ipre[lc], ipre[rc] - (sum[lc] << 1));
    isuf[x] = min(isuf[rc], isuf[lc] - (sum[rc] << 1));
    if (siz[x] == 1) return (void) (ans[x] = ians[x] = INF);
    ans[x] = min(ans[lc], ans[rc]);
    ians[x] = min(ians[lc], ians[rc]);
    if (ans[x].x > suf[lc].x + pre[rc].x)
      ans[x] = Doub(suf[lc].x + pre[rc].x, suf[lc].p, pre[rc].p);
    if (ians[x].x > isuf[lc].x + ipre[rc].x)
      ians[x] = Doub(isuf[lc].x + ipre[rc].x, isuf[lc].p, ipre[rc].p);
  }
  inline void Build(int x = 1, int L = 1, int R = :: n) {
    rev[x] = 0;
    if (L == R) {
      siz[x] = 1;
      if (L % 2 == 0) a[L] = - a[L];
      sum[x] = a[L];
      pre[x] = suf[x] = Mono(a[L], L);
      ipre[x] = isuf[x] = Mono(- a[L], L);
      ans[x] = ians[x] = INF;
      if (L % 2 == 0) a[L] = - a[L];
      return;
    }
    Build(lc, L, mid);
    Build(rc, mid + 1, R);
    UPD(x);
  }
  inline void Del(int p, int x = 1, int L = 1, int R = :: n) {
    // function 2
    if (L == R) {
      siz[x] = 0; sum[x] = 0;
      pre[x] = suf[x] = ipre[x] = isuf[x] = INF;
      ans[x] = ians[x] = INF;
      return;
    }
    DOWN(x);
    if (p <= mid) Del(p, lc, L, mid);
    else Del(p, rc, mid + 1, R);
    UPD(x);
  }
  inline void Rev(int l, int r, int x = 1, int L = 1, int R = :: n) {
    if (!siz[x]) return;
    // function 3
    if (l <= L && R <= r) return (void) REV(x);
    DOWN(x);
    if (l <= mid) Rev(l, r, lc, L, mid);
    if (r > mid) Rev(l, r, rc, mid + 1, R);
    UPD(x);
  }
#undef mid
}
using Seg :: Del;
using Seg :: Rev;
using Seg :: Build;

LL ans[N];
Seg :: Doub tmp;

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i ++)
    scanf("%d", &a[i]), ans[n] += a[i] * sgn[!(i & 1)];
  Build();
  for (int i = n; i > 2; i -= 2) {
    tmp = Seg :: ans[1];
    ans[i - 2] = ans[i] - tmp.x;
    Del(tmp.l); Del(tmp.r);
    Rev(tmp.l, tmp.r);
  }
  int pos = n;
  LL best = - INF, su = 0;
  for (int i = n; i; i --) {
    int k = a[i] * sgn[!(i & 1)];
    if (ans[n] - k - su * 2 > best) {
      best = ans[n] - k - su * 2;
      pos = i;
    }
    su += k;
  }
  Build();
  Del(pos);
  Rev(pos, n);
  ans[n - 1] = best;
  for (int i = n - 1; i > 2; i -= 2) {
    tmp = Seg :: ans[1];
    ans[i - 2] = ans[i] - tmp.x;
    Del(tmp.l); Del(tmp.r);
    Rev(tmp.l, tmp.r);
  }
  for (int i = 1; i <= n; i ++) printf("%lld ", ans[i]);
  puts("");
  return 0;
}
