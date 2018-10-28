#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

typedef long long LL;
const LL mod = 1e9 + 7;

namespace MathCal {
  const int N = 1e6 + 5;
  LL fac[N], inv[N];
  inline LL Pow(LL x, LL exp) {
    LL res = 1;
    for (; exp; exp >>= 1, x = x * x % mod)
      if (exp & 1) res = res * x % mod;
    return res;
  }
  inline void Init() {
    for (int i = fac[0] = 1; i < N; i ++) fac[i] = fac[i - 1] * i % mod;
    inv[N - 1] = Pow(fac[N - 1], mod - 2);
    for (int i = N - 1; i; i --) inv[i - 1] = inv[i] * i % mod;
  }
  inline LL C(int x, int y) {
    if (x < 0 || y < 0) return 0;
    return y > x ? 0 : fac[x] * inv[y] % mod * inv[x - y] % mod;
  }
}
using MathCal :: C;

class LittleElephantAndBoard {
public:
  inline int getNumber(int M, int R, int G, int B) {
    MathCal :: Init();
    int a, b, c;
    a = M - R;
    b = M - G;
    c = M - B;
    if (a > b) swap(a, b);
    if (b > c) swap(b, c);
    if (a > b) swap(a, b);
    if (a < 0) return 0;
    if (a == 0) {
      if (b == 0) return (c <= 1) * 2;
      else {
        if (b + 1 == c) return 2;
        if (b == c) return 4;
        return 0;
      }
    }
    LL ans = 0;
    for (int i = 1, s, d; i <= b; i ++) {
      LL t = C(b - 1, i - 1);
      for (int j = 0; j <= 2; j ++) {
        s = b - i + a - 1 - (i - j);
        d = a + b + 1 - s;
        ans = ( ans + t
                * C(a - 1, i - j) % mod
                * C(d, c - s)
                * (j == 1 ? 2 : 1) ) % mod;
      }
    }
    return (int) ans * 2 % mod;
  }
};
