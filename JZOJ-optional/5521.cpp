#include <bits/stdc++.h>
using namespace std;

const int N = 1e6 + 50;
const int mod = 1e9 + 7;

struct AnsType {
  int ans, tot;
  AnsType() { ans = -1; tot = 0; }
  AnsType(int a, int b): ans(a), tot(b) {}
  inline AnsType operator + (const AnsType &o) const {
    return ans == o.ans ? AnsType( ans, (tot + o.tot) >= mod ?
                                   tot + o.tot - mod : tot + o.tot )
      : ( ans > o.ans ? *this : o );
  }
};

int lc[N], rc[N];
int ql[N], qr[N], n;
int lmost[N], sta[N];

namespace Seg {
#define mid ((L + R) >> 1)
  AnsType tag[N << 2], key[N << 2];
  inline void tagdown(int x) {
    if (tag[x].ans != -1) {
      tag[x << 1] = tag[x << 1] + tag[x];
      tag[x << 1 | 1] = tag[x << 1 | 1] + tag[x];
      tag[x].ans = -1; tag[x].tot = 0;
    }
  }
  inline void tagup(int x) {
    key[x] = key[x << 1] + key[x << 1 | 1];
  }
  inline AnsType Sum(int l, int r, int x = 1, int L = 0, int R = n) {
    if (l > r) return AnsType();
    if (l <= L && R <= r) return key[x];
    tagdown(x); AnsType res;
    if (l <= mid) res = Sum(l, r, x << 1, L, mid);
    if (r > mid) res = res + Sum(l, r, x << 1 | 1, mid + 1, R);
    return res;
  }
  inline AnsType Single(int p, int x = 1, int L = 0, int R = n) {
    if (L == R) return tag[x];
    if (p <= mid) return Single(p, x << 1, L, mid) + tag[x];
    else return Single(p, x << 1 | 1, mid + 1, R) + tag[x];
  }
  inline void Cover(int l, int r, AnsType v, int x = 1, int L = 0, int R = n) {
    if (l <= L && R <= r) { tag[x] = tag[x] + v; return; }
    if (l <= mid) Cover(l, r, v, x << 1, L, mid);
    if (r > mid) Cover(l, r, v, x << 1 | 1, mid + 1, R);
    tagup(x);
  }
  inline void ForcedSet(int p, AnsType v, int x = 1, int L = 0, int R = n) {
    if (L == R) { key[x] = v; return; }
    tagdown(x);
    if (p <= mid) ForcedSet(p, v, x << 1, L, mid);
    else ForcedSet(p, v, x << 1 | 1, mid + 1, R);
    tagup(x);
  }
#undef mid
}

AnsType f[N];

inline void FindLeftmost() {
  int *a = qr;
  int top = 0, ptr = 1;
  lmost[0] = 1;
  for (int i = 1; i <= n; i ++) {
    while (top >= ptr && a[sta[top]] >= a[i]) top --;
    sta[++ top] = i;
    int cur = lmost[i - 1];
    while (i - cur + 1 > a[sta[ptr]]) {
      cur ++;
      if (cur > sta[ptr]) ptr ++;
    }
    lmost[i] = cur;
  }
}

inline int Build() {
  int *a = ql;
  int top = 0;
  for (int i = 1; i <= n; i ++) {
    while (top && a[sta[top]] < a[i]) {
      lc[i] = sta[top];
      if (top > 1 && a[sta[top - 1]] < a[i]) rc[sta[top - 1]] = sta[top];
      top --;
    }
    sta[++ top] = i;
  }
  for (int i = 1; i < top; i ++) rc[sta[i]] = sta[i + 1];
  return sta[1];
}

inline void Dfs(int k, int l, int r) {
  if (r - l + 1 <= 3) {
    for (int i = l; i <= r; i ++) {
      if (!i) { f[i] = AnsType(0, 1); continue; }
      int c = 0, d = 1e9;
      f[i] = f[i] + Seg :: Single(i);
      for (int j = i; j > l; j --) {
        c = max(c, ql[j]);
        d = min(d, qr[j]);
        if (c > d) break;
        if (c <= i - j + 1 && i - j + 1 <= d) f[i] = f[i] + f[j - 1];
      }
      if (f[i].ans >= 0) {
        f[i].ans ++;
        Seg :: ForcedSet(i, f[i]);
      }
    }
    return;
  }
  Dfs(lc[k], l, k - 1);
  
  int h = ql[k];
  int p = max(k, l + h);
  AnsType tmp = Seg :: Sum(l, p - h);
  for (; lmost[p] <= l + 1 && p - h + 1 <= k && p <= r; p ++) {
    f[p] = f[p] + tmp;
    tmp = tmp + f[p - h + 1];
  }
  if (lmost[p] <= l + 1 && p <= r) {
    int al = p, ar = r, mid, rb = p;
    while (al <= ar) {
      mid = (al + ar) >> 1;
      if (lmost[mid] <= l + 1) rb = mid, al = mid + 1;
      else ar = mid - 1;
    }
    Seg :: Cover(p, rb, Seg :: Sum(l, k - 1));
    p = rb + 1;
  }
  for (; p <= r && lmost[p] <= k; p ++)
    f[p] = f[p] + Seg :: Sum( lmost[p] - 1, min(k - 1, p - h) );
  Dfs(rc[k], k, r);
}

int main() {
  freopen("schooldays.in", "r", stdin);
  freopen("schooldays.out", "w", stdout);
  scanf("%d", &n);
  for (int i = 1; i <= n; i ++) {
    scanf("%d%d", &ql[i], &qr[i]);
    if (ql[i] > qr[i]) {
      puts("-1"); return 0;
    }
  }
  FindLeftmost();
  Seg :: ForcedSet(0, AnsType(0, 1));
  Dfs(Build(), 0, n);
  printf("%d ", f[n].ans);
  if (f[n].ans != -1) printf("%d\n", f[n].tot);
  return 0;
}
