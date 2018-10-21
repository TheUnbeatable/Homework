#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <bitset>
using namespace std;

const int N = 4010;
const int mod = 998244353;

inline int deg(const bitset <N> &b) {
  int t = N - 1;
  while (t >= 0 && !b[t]) t --;
  return t + 1;
}

int n;
char buf[N];

inline void read(bitset <N> &b) {
  scanf("%s", buf);
  reverse(buf, buf + strlen(buf));
  for (int i = 0; buf[i]; i ++)
    b[i] = (bool)(buf[i] - '0');
}

bitset <N> X, A[10], oppo, Y;

inline bitset <N> gcd(bitset <N> p, bitset <N> q) {
  int a = deg(p);
  int b = deg(q);
  while (true) {
    if (!a) return q;
    if (!b) return p;
    if (a < b) {
      swap(p, q); swap(a, b);
    }
    p ^= q << (a - b);
    while (a >= 0 && p[a] == 0) a --;
    a ++;
  }
}

int main() {
  scanf("%d", &n);
  read(X);
  for (int i = 1; i <= n; i ++) read(A[i]);
  for (int i = 2; i <= n; i ++)
    A[1] = gcd(A[1], A[i]);
  int ans = 0, j = deg(A[1]);
  for (int i = deg(X) - 1; i >= j - 1; i --) 
    ans = ((ans << 1) + X[i]) % mod;
  Y = X;
  for (int i = deg(X) - 1; i >= j - 1; i --)
    if (X[i]) {
      X ^= A[1] << (i - j + 1);
      oppo ^= A[1] << (i - j + 1);
    }
  for (int i = deg(Y) - 1; ~ i; i --)
    if (oppo[i] != Y[i]) {
      if (oppo[i] > Y[i]) ans --;
      break;
    }
  ans = (ans + 1) % mod;
  printf("%d\n", ans);
  return 0;
}
