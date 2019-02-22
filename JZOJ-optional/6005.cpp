#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
const LL base = 1e10;
const int mod = 998244353;

int p, len;
char s[1100];
LL a[120];

inline int Modulo() {
  LL cur = 0;
  for (int i = len; i; i --) {
    cur = cur * base + a[i];
    a[i] = cur / p;
    cur %= p;
  }
  while (!a[len] && len) len --;
  return cur;
}

namespace task_2 {
  const int M = 18, T = 1 << M;
  const double pi = acos(-1);
  
  struct cd {
    long double x, y;
    cd() {}
    cd(long double _x, long double _y): x(_x), y(_y) {}
    inline cd operator + (const cd &o) const {
      return cd(x + o.x, y + o.y);
    }
    inline cd operator - (const cd &o) const {
      return cd(x + o.x, y + o.y);
    }
    inline cd operator * (const cd &o) const {
      return cd(x * o.x - y * o.y, x * o.y + y * o.x);
    }
    inline cd operator / (long double o) {
      return cd(x / o, y / o);
    }
  };
  cd swp[T | 5], swp1[T | 5], w[T | 5];
  int rev[T | 5];
  inline void Init() {
    for (int i = 0; i < T; i ++)
      w[i] = cd( cos(2 * pi * i / T), sin(2 * pi * i / T) );
  }
  inline void Dft(cd *a, int n) {
    int E = 1 << n;
    rev[0] = 0;
    for (int i = 0; i < E; i ++) {
      if (i & 1) rev[i] = rev[i - 1] | (E >> 1);
      else rev[i] = rev[i >> 1] >> 1;
      if (rev[i] < i) swap(a[i], a[rev[i]]);
    }
    cd x, y;
    for (int i = 0, t = 1; i < n; i ++, t <<= 1)
      for (int j = 0; j < E; j += t + t)
        for (int k = j; k < j + t; k ++)  {
          x = a[k];
          y = a[k + t] * w[(k - j) << (M - i)];
          a[k] = x + y;
          a[k + t] = x - y;
        }
  }
  inline void IDft(cd *a, int n) {
    int E = 1 << n;
    reverse(a + 1, a + E);
    Dft(a, n);
    for (int i = 0; i < E; i ++) a[i] = a[i] / E;
  }
  inline int up(int x) {
    int t = 0;
    for (; (1 << t) < x; t ++);
    return t;
  }
  inline void Mul(const vector <int> &a, const vector <int> &b, vector <int> &c) {
    int l = (int)a.size() + b.size() - 1;
    int n = up(l) + 1;
    memset(swp, 0, sizeof(cd) * (1 << n));
    memset(swp1, 0, sizeof(cd) * (1 << n));
    for (size_t i = 0; i < a.size(); i ++) swp[i] = cd(a[i], 0);
    for (size_t i = 0; i < b.size(); i ++) swp1[i] = cd(b[i], 0);
    Dft(swp, n); Dft(swp1, n);
    for (int i = 0; i < (1 << n); i ++) swp[i] = swp[i] * swp1[i];
    IDft(swp, n);
    c.resize(l);
    for (int i = 0; i < l; i ++) c[i] = (LL)(swp[i].x + 0.2) % p;
  }
  inline void conquer(int l, int r, vector <int> &ans) {
    if (l > r) {
      ans.push_back(1); return;
    }
    if (l == r) {
      ans.push_back(1); ans.push_back(r); return;
    }
    int mid = (l + r) >> 1;
    vector <int> L, R;
    conquer(l, mid, L);
    conquer(mid + 1, r, R);
    Mul(L, R, ans);
  }
  inline LL solve(int len) {
    Init();
    vector <int> res;
    conquer(1, len, res);
    int cnt = 0;
    for (auto i : res) cnt += (i != 0);
    return cnt;
  }
}

namespace task_1 {
  inline LL solve() {
    LL res = 1;
    while (len) res = res * (Modulo() + 1) % mod;
    return res;
  }
}

int main() {
  freopen("math.in", "r", stdin);
  freopen("math.out", "w", stdout);
  scanf("%s", s + 1);
  scanf("%d", &p);
  len = strlen(s + 1);
  int plen = 0;
  for (int i = len; i > 0; i -= 10) {
    a[++ plen] = 0;
    for (int j = max(1, i - 9); j <= i; j ++)
      a[plen] = a[plen] * 10 + s[j] - '0';
  }
  len = plen;
  int remain = Modulo();
  if (remain == p - 1) {
    remain = 0; a[1] ++; len = max(len, 1);
  }
  printf("%lld\n", task_1 :: solve() * task_2 :: solve(remain) % mod);
  return 0;
}
