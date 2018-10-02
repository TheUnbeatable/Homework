#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

typedef long long LL;

LL n = 1e15;

int main() {
  LL P = 8;
  for (LL i = 5; i <= n; ) {
    LL m = P, t;
    for (LL j = 2; j * j <= P; j ++) {
      if (P % j) continue;
      t = P / j;
      m = min( m, ( (i - 1) / j + 1 ) * j );
      m = min( m, ( (i - 1) / t + 1 ) * t );
    }
    if (m > n) break;
    P = P + __gcd(P, m) - 1;
    i = m + 1;
  }
  cout << P + n + 1 << endl;
  return 0;
}
