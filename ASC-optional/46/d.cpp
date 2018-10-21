#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
#include <iomanip>
#include <cmath>
using namespace std;

typedef long long LL;

const LL Mod = 258280327;

namespace Poly {
#define ri register int
#define Int(x) (((LL)(x + 0.5)) % Mod)
  typedef vector <LL> poly;
  const int S = 19, N = 1 << S | 5;
  const double PI = acos(-1);

  struct cd {
    double x, y;
    cd(LL _x, LL _y) : x(_x), y(_y) {}
    cd(int _x, int _y) : x(_x), y(_y) {}
    cd(double _x = 0, double _y = 0) : x(_x), y(_y) {}
    inline cd operator + (const cd &o) const { return cd( x + o.x, y + o.y ); }
    inline cd operator - (const cd &o) const { return cd( x - o.x, y - o.y ); }
    inline cd operator * (const double o) const { return cd( x * o, y * o); }
    inline cd operator / (const double o) const { return cd( x / o, y / o); }
    inline cd operator * (const cd &o) const { return cd( x * o.x - y * o.y, x * o.y + y * o.x ); }
    inline cd operator / (const cd &o) const { return cd( x * o.x + y * o.y, y * o.x - x * o.y ) / ( o.x * o.x + o.y * o.y ); }
    inline void operator += (const cd &o) { x += o.x; y += o.y; }
    inline cd conj() { return cd( x, - y); }
    friend ostream& operator << (ostream &o, cd c) {
      o << fixed << setprecision(5) << "(" << c.x << "," << c.y << ")";
      return o;
    }
  };
  inline cd conj(const cd &o) { return cd( o.x, - o.y ); }
  typedef vector <cd> fpoly;

  int rev[N];
  cd W[N];
  
  inline int Up(int x) {
    int d = 0;
    while ((1 << d) < x) d ++;
    return d;
  }
  inline void FFT_Init() {
    for (int i = (1 << S) - 1; ~ i; i --)
      W[i] = cd( cos(2 * PI * i / (1 << S)), sin(2 * PI * i / (1 << S)) );
  }
  inline void Dft(fpoly &a, int n) {
    int E = 1 << n; a.resize(E);
    for (int i = 0; i < E; i ++) {
      if (i & 1) rev[i] = rev[i - 1] | (E >> 1);
      else rev[i] = rev[i >> 1] >> 1;
      if (rev[i] < i) swap(a[rev[i]], a[i]);
    }
    register cd x, y;
    for (int i = 1, d = 1; d <= n; i <<= 1, d ++)
      for (int j = 0; j < E; j += 1 << d)
        for (int k = j; k < j + i; k ++) {
          x = a[k];
          y = a[k + i] * W[(k - j) << (S - d)];
          a[k] = x + y; a[k + i] = x - y;
        }
  }
  inline void IDft(fpoly &a, int n) {
    a.resize(1 << n);
    reverse(a.begin() + 1, a.end());
    Dft(a, n);
    double inv = 1.0 / (1 << n);
    for (int i = (1 << n) - 1; ~ i; i --) a[i] = a[i] * inv;
  }
  inline void SuperMul(const poly &a, const poly &b, poly &c) {
    fpoly s0, s1, t0, t1;
    int len = a.size() + b.size() - 1, n = Up(len);
    LL base = sqrt(Mod) + 1;
    t0.resize(1 << n); t1.resize(1 << n);
    s0.resize(1 << n); s1.resize(1 << n);
    for (size_t i = 0; i < a.size(); i ++)
      t0[i] = cd( a[i] / base, a[i] % base );
    for (size_t i = 0; i < b.size(); i ++)
      t1[i] = cd( b[i] / base, b[i] % base );
    Dft(t0, n); Dft(t1, n);
    cd p, q, xx, yy;
    cd a0, a1, b0, b1;
    for (int i = (1 << n) - 1; ~ i; i --) {
      p = t0[i]; q = t0[i ? (1 << n) - i : 0];
      a0 = (p + conj(q)) / 2;
      a1 = (p - conj(q)) / cd(0, 2);
      p = t1[i]; q = t1[i ? (1 << n) - i : 0];
      b0 = (p + conj(q)) / 2;
      b1 = (p - conj(q)) / cd(0, 2);
      s0[i] = a0 * b0 + a0 * b1 * cd(0, 1);
      s1[i] = a1 * b0 + a1 * b1 * cd(0, 1);
    }
    IDft(s0, n); IDft(s1, n);
    c.resize(len);
    LL base2 = base * base % Mod, a0b0, a0b1, a1b0, a1b1;
    for (int i = len - 1; ~ i; i --) {
      a0b0 = Int(s0[i].x); a0b1 = Int(s0[i].y);
      a1b0 = Int(s1[i].x); a1b1 = Int(s1[i].y);
      c[i] = base2 * (a0b0 % Mod) % Mod + base * ((a0b1 + a1b0) % Mod) % Mod + a1b1 % Mod;
      c[i] %= Mod;
    }
  }
#undef Int
}
using namespace Poly;

LL ans[1 << 17 | 5];
poly R, B;

inline void Mulx(poly &a) {
  a.push_back(0);
  for (int i = (int)a.size() - 2; ~ i; i --) a[i + 1] = a[i];
  a[0] = 0;
}

inline void Add(poly &a, const poly &b) {
  for (size_t i = 0; i < b.size(); i ++) {
    a[i] += b[i];
    if (a[i] >= Mod) a[i] -= Mod;
  }
}

int main() {
#ifdef ONLINE_JUDGE
  freopen("dichromatic.in", "r", stdin);
  freopen("dichromatic.out", "w", stdout);
#endif
  FFT_Init();
  int k, h;
  scanf("%d%d", &k, &h);
  R.reserve(1 << 17 | 5);
  R.push_back(1);
  R.push_back(1);
  ans[1] = 1;
  for (int i = 1; i <= h; i ++) {
    SuperMul(R, R, B);
    Mulx(B);
    B.resize( min( (int)B.size(), 1 << 17 | 1 ) );
    SuperMul(B, B, R);
    for (auto it : R) if (it < 0) { cerr << i << endl; break; }
    Mulx(R);
    Add(R, B);
    B.clear();
    R.resize( min( (int)R.size(), 1 << 17 | 1 ) );
    for (size_t j = 0; j < R.size(); j ++) {
      ans[j] += R[j];
      if (ans[j] >= Mod) ans[j] -= Mod;
    }
  }
  for (int n; k; k --) {
    scanf("%d", &n);
    printf("%lld ", ans[n]);
  }
  puts("");
  return 0;
}
