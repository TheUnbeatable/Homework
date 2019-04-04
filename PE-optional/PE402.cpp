#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
const int mod = 1e9;
const LL n = 1234567890123ll;

inline int calc(int a, int b, int c) {
  return __gcd( __gcd( __gcd( 24, 6 * a + 12 ),
                       2 * b + 2 ), a + b + c + 1 );
}

int a[50], b[30], C[5][5], S[5][5], tab[101];
int u[50], v[50], w[50], id[5][5];

struct Mat {
  LL a[15][15];
  Mat() { memset(a, 0, sizeof a); }
};

inline Mat Mul(const Mat &a, const Mat &b) {
  static Mat res;
  for (int i = 0; i < 15; i ++)
    for (int j = 0; j < 15; j ++) {
      LL ans = 0;
      for (int k = 0; k < 15; k ++)
        ( ans += a.a[i][k] * b.a[k][j] ) %= mod;
      res.a[i][j] = ans;
    }
  return res;
}

inline Mat fpow(Mat x, LL exp) {
  Mat res;
  for (int i = 0; i < 15; i ++) res.a[i][i] = 1;
  for (; exp; exp >>= 1, x = Mul(x, x))
    if (exp & 1) res = Mul(res, x);
  return res;
}

LL ANS = 0;
int vec[20];
LL ans[10], d[10];

int main() {
  a[1] = b[1] = 1;
  for (int i = 2; i <= 48; i ++)
    a[i] = (a[i - 1] + a[i - 2]) % 24;
  for (int i = 2; i <= 24; i ++) b[i] = b[i - 1] + b[i - 2];
  for (int i = 1; i <= 24; i ++) b[i] /= 24;
  S[0][0] = 1;
  for (int i = 0; i <= 4; i ++) {
    C[i][0] = 1;
    for (int j = 1; j <= i; j ++) {
      C[i][j] = C[i - 1][j - 1] + C[i - 1][j];
      S[i][j] = S[i - 1][j - 1] + S[i - 1][j] * (i - 1);
    }
  }
  for (int i = 1; i <= 96; i ++)
    for (int j = 1; j <= 96; j ++)
      for (int k = 1; k <= 96; k ++)
        tab[max(max(i, j), k)] += calc(i, j, k);
  for (int i = 1; i <= 96; i ++) tab[i] += tab[i - 1];
  for (int i = 0, k = 0; i < 4; i ++)
    for (int j = 0; i + j < 4; j ++, k ++) id[i][j] = k;
  for (int s = 1; s <= 24; s ++) {
    memset(u, 0, sizeof u);
    memset(v, 0, sizeof u);
    memset(w, 0, sizeof u);
    u[s] = 1;
    v[s - 1] = 1;
    for (int i = s + 1; i <= s + 24; i ++) {
      u[i] = u[i - 1] + u[i - 2];
      v[i] = v[i - 1] + v[i - 2];
      w[i] = w[i - 1] + w[i - 2] + (a[i - 1] + a[i - 2] >= 24);
    }
    Mat trans;
    int x = s + 24, y = x - 1;
    for (int i = 0; i < 4; i ++)
      for (int j = 0; i + j < 4; j ++)
        for (LL a = 0, pa = 1; a <= i;         a ++, (pa *= u[x]) %= mod)
        for (LL b = 0, pb = 1; a + b <= i;     b ++, (pb *= v[x]) %= mod)
        for (LL c = 0, pc = 1; a + b + c <= i; c ++, (pc *= w[x]) %= mod)
        if (a + b + c == i)
        for (LL d = 0, pd = 1; d <= j;         d ++, (pd *= u[y]) %= mod)
        for (LL e = 0, pe = 1; d + e <= j;     e ++, (pe *= v[y]) %= mod)
        for (LL f = 0, pf = 1; d + e + f <= j; f ++, (pf *= w[y]) %= mod)
        if (d + e + f == j)
          ( trans.a[ id[a + d][b + e] ][ id[i][j] ] +=
            pa * pb % mod * pc % mod * pd % mod * pe % mod * pf % mod
            * C[i][a] * C[i - a][b] * C[j][d] * C[j - d][e] ) %= mod;
    for (int i = 0; i < 4; i ++) {
      trans.a[ id[i][0] ][ 10 + i ] = 1;
      trans.a[ 10 + i ][ 10 + i ] = 1;
    }

    trans = fpow(trans, (n - s) / 24 + 1);
    
    for (LL i = 0, pa = 1; i < 4; i ++, pa = pa * b[s] % mod)
      for (LL j = 0, pb = 1; i + j < 4; j ++, pb = pb * b[s - 1] % mod)
        vec[ id[i][j] ] = pa * pb % mod;
    for (int i = 0; i < 4; i ++) {
      ans[i] = 0;
      for (int j = 0; j < 10; j ++)
        ( ans[i] += vec[j] * trans.a[j][i + 10] ) %= mod;
    }
    for (int i = 3; i; i --) {
      LL tmp = 0;
      for (int j = i, sgn = 1; j; j --, sgn = - sgn)
        tmp += sgn * S[i][j] * ans[j];
      ans[i] = (tmp % mod + mod) % mod;
    }
    for (int i = 0; i < 4; i ++) d[i] = tab[i * 24 + a[s]];
    for (int i = 0, fac = 1; i < 4; i ++) {
      if (i) fac *= i;
      assert(d[0] % fac == 0);
      ( ANS += (d[0] / fac) * ans[i] ) %= mod;
      for (int j = 0; j <= 2 - i; j ++)
        d[j] = d[j + 1] - d[j];
    }
  }
  ANS = (ANS % mod + mod - tab[1]) % mod;
  printf("%lld\n", ANS);
  return 0;
}
