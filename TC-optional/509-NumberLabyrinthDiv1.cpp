#include <cstdio>
#include <iostream>
#include <map>
#include <ctime>
#include <vector>
#include <cstring>
#include <algorithm>
#define ri register int
using namespace std;

typedef long long LL;
typedef vector <int> VI;
const int N = 45;
const LL mod = 1e9 + 9;

namespace MathCal {
  typedef long long LL;
  const int M = 1e6 + 5;
  
  LL fac[M], inv[M];
  inline LL pow(LL x, LL exp) {
    LL res = 1;
    for (; exp; exp >>= 1, x = x * x % mod)
      if (exp & 1) res = res * x % mod;
    return res;
  }
  inline void pre() {
    for (int i = fac[0] = 1; i < M; i ++) fac[i] = fac[i - 1] * i % mod;
    inv[M - 1] = pow(fac[M - 1], mod - 2);
    for (int i = M - 1; i; i --) inv[i - 1] = inv[i] * i % mod;
  }
  inline LL C(int x, int y) {
    return y > x ? 0 : fac[x] * inv[y] % mod * inv[x - y] % mod;
  }
}
using namespace MathCal;

int was = 0;

class NumberLabyrinthDiv1 {
private :
  struct Obj {
    int x, y, v, id;
    Obj() {}
    Obj(int _x, int _y, int _v = 0) : x(_x), y(_y), v(_v), id(0) {};
    inline bool operator < (const Obj &o) const { return x != o.x ? x < o.x : y < o.y; }
    inline bool operator <= (const Obj &o) const { return x <= o.x && y <= o.y; }
    inline bool operator == (const Obj &o) const { return x == o.x && y == o.y; }
    inline Obj R() { return Obj(x, y + v); }
    inline Obj D() { return Obj(x + v, y); }
  } a[N], b[N], R[N], D[N], arr[N * 3];
  int n;
  LL dp[N][12], rec[N][N][12];
public :
  inline LL count(Obj s, Obj t, int step) {
    if (!(s <= t)) return 0;
    LL ans = 0;
    int x = t.x - s.x, y = t.y - s.y;
    if (!x && !y) return step == 0;
    if (!x || !y) {
      if (step < 1) return 0;
      if (!x) swap(x, y);
      return C(x - 1, step - 1);
    }
    if (step < 2) return 0;
    step -= 2;
    for (ri i = 0; i <= step; i ++)
      (ans += C(x - 1, i) * C(y - 1, step - i) % mod * C(step + 2, i + 1)) %= mod;
    return ans;
  }
  inline vector <LL> calc(Obj s, Obj t, int K) {
    static LL dp[N][12];
    int m = 0;
    for (ri i = 1; i <= n; i ++)
      if (s <= a[i] && a[i] <= t) b[++ m] = a[i];
    for (ri i = 1; i <= m; i ++)
      for (ri k = 0; k <= K; k ++) {
        dp[i][k] = count(s, b[i], k);
        for (ri j = 1; j < i; j ++)
          for (ri l = 0; l <= k; l ++)
            if (dp[j][l]) ( dp[i][k] -= rec[b[j].id][b[i].id][k - l] * dp[j][l] ) %= mod;
      }
    vector <LL> res; res.resize(K + 1);
    for (int i = 0; i <= K; i ++) res[i] = dp[m][i];
    return res;
  }
  inline int getNumberOfPaths(VI X, VI Y, VI val, int Ex, int Ey, int K) {
    if (K < 2) return 0;
    pre(); n = 0;
    for (size_t i = 0; i < X.size(); i ++)
      if (X[i] <= Ex && Y[i] <= Ey)
        a[++ n] = (Obj) { X[i], Y[i], val[i] };
    a[++ n] = (Obj) { Ex, Ey };
    sort(a + 1, a + n + 1);
    for (ri i = 1; i <= n; i ++) a[i].id = i;
    for (ri i = 1; i <= n; i ++)
      for (ri j = 1; j <= n; j ++)
        for (ri k = 0; k <= K; k ++)
          rec[i][j][k] = count(a[i], a[j], k);
    vector <LL> A, B;
    for (ri i = 1; i <= n; i ++) {
      A = calc(Obj(0, 0), a[i], K);
      for (ri k = 0; k <= K; k ++) dp[i][k] = A[k];
    }
    for (ri i = 1; i <= n; i ++)
      for (ri j = 1; j < i; j ++) {
        A = calc(a[j].R(), a[i], K);
        B = calc(a[j].D(), a[i], K);
        for (ri k = 0; k <= K; k ++)
          for (ri l = 0; l <= k; l ++)
            if (dp[j][l]) ( dp[i][k] += dp[j][l] * (A[k - l] + B[k - l]) ) %= mod;
      }
    LL ans = 0;
    for (int i = 0; i <= K; i ++) ans += dp[n][i];
    return (int) (ans % mod);
  }
};
