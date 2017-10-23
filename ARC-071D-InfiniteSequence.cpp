#include <cstdio>
#include <iostream>
using namespace std;

const int N = 1e6 + 5;
const int mod = 1e9 + 7;

int dp[N], pref[N];

inline void modadd(int &x, int y) {
  x += y;
  if (x >= mod) x -= mod;
}

int main() {
  int n;
  scanf("%d", &n);
  pref[1] = dp[1] = n;
  dp[2] = 1LL * n * n % mod;
  pref[2] = pref[1];
  modadd(pref[2], dp[2]);
  for (int i = 3; i <= n; i ++) {
    dp[i] = dp[i - 1];
    if (i > 2) modadd(dp[i], 1LL * (n - 1) * (n - 1) % mod);
    if (i >= 3) modadd(dp[i], pref[i - 3]);
    modadd(dp[i], n - i + 2);
    pref[i] = pref[i - 1];
    modadd(pref[i], dp[i]);
  }
  printf("%d\n", dp[n]);
  return 0;
}
