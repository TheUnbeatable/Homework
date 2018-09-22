#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 16;
const int mod = 1e9 + 7;

inline int pow(int x, int exp) {
  int res = 1;
  for (; exp; exp >>= 1, x = 1ll * x * x % mod)
    if (exp & 1) res = 1ll * res * x % mod;
  return res;
}

class Nim {
private :
  bool notp[1 << N | 5];
  int a[1 << N | 5], res[1 << N | 5];
  inline void Dft(int *a, int len) {
    register int x;
    for (int i = 0, f = 1; i < len; i ++, f <<= 1)
      for (int j = 0; j < (1 << len); j ++)
        if (!(j & f)) {
          x = a[j] << 1;
          a[j] += a[j | f];
          a[j | f] = x - a[j];
          if (a[j] >= mod) a[j] -= mod;
          if (a[j | f] < 0) a[j | f] += mod;
        }
  }
public :
  inline int count(int K, int L) {
    memset(notp, 0, sizeof notp);
    memset(a, 0, sizeof a);
    memset(res, 0, sizeof res);
    for (int i = 2; i <= L; i ++)
      if (!notp[i]) {
        a[i] = 1;
        for (int j = i + i; j <= L; j += i) notp[j] = 1;
      }
    int w = 0;
    while ((1 << w) <= L) w ++;
    res[0] = 1;
    int inv = pow(1 << w, mod - 2);
    Dft(res, w);
    Dft(a, w);
    for (; K; K >>= 1) {
      if (K & 1) {
        for (int i = 0; i < (1 << w); i ++)
          res[i] = 1ll * res[i] * a[i] % mod;
      }
      if (K > 1) {
        for (int i = 0; i < (1 << w); i ++)
          a[i] = 1ll * a[i] * a[i] % mod;
      }
    }
    Dft(res, w);
    return 1ll * res[0] * inv % mod;
  }
};
