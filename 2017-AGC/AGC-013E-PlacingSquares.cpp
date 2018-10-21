#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
#define rep(i, x, y) for (int i = x; i <= y; i ++)
using namespace std;

const int N = 1e5 + 50;
const int mod = 1e9 + 7;

struct Matrix {
  int a[3][3];
  Matrix() { memset(a, 0, sizeof a); }
  inline int* operator [] (int i) { return a[i]; }
  inline Matrix operator * (const Matrix &o) const {
    Matrix ret;
    long long tmp;
    rep(i, 0, 2) rep(j, 0, 2) {
      tmp = 0;
      rep(k, 0, 2) tmp += 1LL * a[i][k] * o.a[k][j];
      ret.a[i][j] = tmp % mod;
    }
    return ret;
  }
} cut, Ncut, ans;

int n, m, a[N];

inline Matrix Pow(Matrix x, int exp) {
  Matrix res;
  res[0][0] = res[1][1] = res[2][2] = 1;
  for (; exp; exp >>= 1, x = x * x)
    if (exp & 1) res = res * x;
  return res;
}

int main() {
  scanf("%d%d", &n, &m);
  rep(i, 1, m) scanf("%d", &a[i]);
  cut[0][0] = cut[1][0] = 2;
  cut[0][1] = cut[0][2] = cut[1][1] = cut[2][0] = cut[2][1] = cut[2][2] = 1;
  rep(i, 0, 2) rep(j, 0, i) Ncut[i][j] = 1;
  Ncut[1][0] = 2;
  rep(i, 0, 2) ans[0][i] = 1;
  rep(i, 1, m)
    ans = ans * Pow(cut, a[i] - a[i - 1] - 1) * Ncut;
  ans = ans * Pow(cut, n - a[m] - 1);
  printf("%d\n", ans[0][0]);
  return 0;
}
