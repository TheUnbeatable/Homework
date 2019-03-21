#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
const int N = 1e6 + 5;
const int mod = 1e9 + 7;

int fac[N], inv[N], ifac[N];

inline LL Pow(LL x, LL exp) {
  exp %= mod - 1;
  if (exp < 0) exp += mod - 1;
  LL res = 1;
  for (; exp; exp >>= 1, x = x * x % mod)
    if (exp & 1) res = res * x % mod;
  return res;
}

inline void Init() {
  for (int i = fac[0] = 1; i < N; i ++)
    fac[i] = (LL)fac[i - 1] * i % mod;
  ifac[N - 1] = Pow(fac[N - 1], mod - 2);
  for (int i = N - 1; i; i --) {
    ifac[i - 1] = (LL)ifac[i] * i % mod;
    inv[i] = (LL)ifac[i] * fac[i - 1] % mod;
  }
}

LL A, B, C;
int pref[N];

inline void solve() {
  scanf("%lld%lld%lld", &A, &B, &C);
  C --;
  if (A > B) swap(A, B);
  LL ans = 1, tot = Pow(2, C), cur = 1, md = C % mod + mod;
  for (int i = pref[0] = 1; i <= A && i <= C; i ++) {
    cur = cur * (md - i + 1) % mod * inv[i] % mod;
    pref[i] = pref[i - 1] + cur;
    pref[i] >= mod ? pref[i] -= mod : 0;
  }
  md = (A + B) % mod + mod;
  for (int i = 1; i <= A; i ++)
    ans = ans * (md - i + 1) % mod * inv[i] % mod;
  ans = ans * tot % mod;
  cur = 1;
  md = B % mod + mod;
  for (int i = 0; i <= A && i <= C; i ++) {
    ans -= cur * ( tot - (i ? pref[i - 1] : 0) ) % mod;
    cur = cur * (A - i) % mod * (md - i) % mod
      * inv[i + 1] % mod * inv[i + 1] % mod;
  }
  ans = (ans % mod + mod) % mod;
  printf("%lld\n", ans);
}

int main() {
  freopen("shishui.in", "r", stdin);
  freopen("shishui.out", "w", stdout);
  Init();
  int T; scanf("%d", &T);
  while (T --) solve();
  return 0;
}
