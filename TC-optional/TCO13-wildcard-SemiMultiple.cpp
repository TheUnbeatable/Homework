#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 2050;
const int mod = 1e9 + 7;

inline int Add(int x, int y, int mo = mod) {
  return (x + y >= mo) ? (x + y - mo) : (x + y);
}

inline int Sub(int x, int y, int mo = mod) {
  return (x < y) ? (x - y + mo) : (x - y);
}

class SemiMultiple {
private:
  int n, m, buc[N], cp[N], swp[N];
  inline void Ins(int x) {
    for (int i = 0, j = x % m; i < m; i ++, j = Add(j, 1, m))
      swp[j] = buc[i];
    for (int i = 0; i < m; i ++)
      buc[i] = Add(buc[i], swp[i]);
  }
  inline void Del(int x) {
    int xa = 0;
    for (int i = 0, j = 0; i < m; i ++, j = Sub(j, x, m))
      xa = Sub(buc[j], xa);
    xa = 1ll * xa * ((mod + 1) >> 1) % mod;
    for (int i = 0, j = 0; i < m; i ++, j = Sub(j, x, m)) {
      swp[j] = xa; xa = Sub(buc[j], xa);
    }
    memcpy(buc, swp, sizeof buc);
  }
public:
  inline int count(int N, int M) {
    memset(buc, 0, sizeof buc);
    buc[0] = 1;
    n = N; m = M;
    int t = m & (- m), c = 0;
    m /= t;
    for (; t > 1; t >>= 1) c ++;
    if (n <= c) return n;
    n -= c;
    for (int i = 1, t = 1; i <= n; i ++, t = Add(t, t, m)) Ins(t);
    for (int i = 1; i <= n; i ++, t = Add(t, t));
    long long ans = (1ll * c * buc[0] + t - buc[0] + mod) % mod;
    memcpy(cp, buc, sizeof buc);
    for (int k = 1; k < m; k ++) {
      int MustAdd = 0;
      for (int i = 1, t = 1; i <= n; i ++, t = Add(t, t, m)) {
        if (t == k) Del(t);
        if (t == m - k) Del(t), MustAdd ++;
      }
      MustAdd = MustAdd * (m - k) % m;
      ans = Sub(ans, buc[Sub(k, MustAdd, m)]);
      memcpy(buc, cp, sizeof buc);
    }
    return (int) ans;
  }
};
