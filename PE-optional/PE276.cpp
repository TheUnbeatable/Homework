#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <bitset>
using namespace std;

typedef __int128 LL;
const int N = 1e7 + 50;

bitset <N> notp;
int pri[N / 4], m, mu[N], arr[20], n = 1e7;

inline void Init() {
  for (int i = 2; i <= n; i ++) {
    if (!notp[i]) {
      pri[++ m] = i; mu[i] = - 1;
    }
    for (int j = 1; j <= m; j ++) {
      int t = pri[j] * i;
      if (t >= N) break;
      notp[t] = 1;
      if (i % pri[j] == 0) {
        mu[t] = 0; break;
      }
      mu[t] = - mu[i];
    }
  }
  mu[1] = 1;
}

inline void InitArr() {
  for (int s = 1; s < 12; s ++) {
    int &cnt = arr[s + 1];
    for (int i = 1; i <= s; i ++)
      for (int j = i; j + i <= s; j ++)
        for (int k = j; k < i + j && i + j + k <= s; k ++) cnt ++;
  }
}

inline LL poly(LL n) {
  return n * n * n + 3 * n * n - 9 * n;
}

inline LL _poly(LL n) {
  return n * n * n + 3 * n * n;
}

inline LL calc(int n) {
  n ++;
  int m = n % 12;
  if (m & 1) return (poly(n) - poly(m)) / 144 + arr[m];
  else return (_poly(n) - _poly(m)) / 144 + arr[m];
}

inline void write(LL x) {
  if (!x) return (void) putchar('0');
  if (x < 0) { x = - x; putchar('-'); }
  static int buf[50];
  int len = 0;
  for (; x; x /= 10) buf[++ len] = x % 10;
  for (; len; len --) putchar('0' + buf[len]);
}

LL ans;

int main() {
  Init();
  InitArr();
  for (int i = 1; i <= n; i ++)
    ans += mu[i] * calc(n / i);
  write(ans);
  return 0;
}
