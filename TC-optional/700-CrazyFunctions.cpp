#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

typedef long long LL;
const int N = 5050;
const LL mod = 1e9 + 7;
const LL sqr = mod * mod;

namespace MathCal {
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
    return y > x ? 0 : fac[x] * inv[y] % mod * inv[x - y] % mod;
  }
}
using MathCal :: C;

int S[N][N];

class CrazyFunctions {
private:
  int treeCount[N], res[N];
  inline void Mul(int *a, int *b, int n) {
    int pa = 0, pb = 0;
    while (!a[pa] && pa <= n) pa ++;
    while (!b[pb] && pb <= n) pb ++;
    for (int i = n; i >= pa; i --) {
      LL tmp = 0;
      for (int j = pb; j <= i && i - j >= pa; j ++) {
        if (!a[i - j] || !b[j]) continue;
        tmp += 1ll * a[i - j] * b[j];
        if (tmp >= sqr) tmp -= sqr;
      }
      a[i] = tmp % mod;
    }
  }
public:
  inline int count(int n, int k) {
    MathCal :: Init();
    treeCount[0] = 1;
    for (int i = 1; i <= n - k + 1; i ++)
      treeCount[i] = MathCal :: Pow(i, i - 1) * MathCal :: inv[i] % mod;
    treeCount[0] = 0;
    int K = k;
    bool fir = 1;
    for (; k; k >>= 1) {
      if (k & 1) {
        if (fir) memcpy(res, treeCount, sizeof res);
        else Mul(res, treeCount, n);
        fir = 0;
      }
      if (k > 1) Mul(treeCount, treeCount, n);
    }
    S[0][0] = 1;
    for (int i = 1; i <= K; i ++)
      for (int j = 1; j <= i; j ++)
        S[i][j] = (1ll * S[i - 1][j] * (i - 1) + S[i - 1][j - 1]) % mod;
    LL su = 0;
    for (int i = 1; i <= K; i ++) su += S[K][i];
    su %= mod;
    return su * res[n] % mod * MathCal :: fac[n] % mod * MathCal :: inv[K] % mod;
  }
};
