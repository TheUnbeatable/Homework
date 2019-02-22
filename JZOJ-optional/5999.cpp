#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
const int N = 1 << 16, M = 5e4;
const int mod = 998244353;
const int IN = 998229121, I6 = 166374059, I24 = 291154603, I2 = (mod + 1) / 2;
const int THRESH = 64;

int phi[N], notp[N], n, f, s;
LL tab[N + 5];

inline void initPhi() {
  for (int i = 1; i < N; i ++) phi[i] = i;
  for (int i = 2; i < N; i ++)
    if (!notp[i]) {
      for (int j = i; j < N; j += i)
        phi[j] = phi[j] / i * (i - 1), notp[j] = 1;
    }
}

inline void Dft(LL *a) {
  int y;
  for (int i = 0; i < 16; i ++) {
    int d = 1 << i;
    for (int j = 0; j < N; j ++)
      if ((j & d) == 0) {
        y = a[j + d];
        a[j + d] = a[j] - y;
        if (a[j + d] < 0) a[j + d] += mod;
        a[j] = a[j] + y;
        if (a[j] >= mod) a[j] -= mod;
      }
  }
}

inline void solve3() {
  static LL a[N + 3];
  LL ans = 0;
  for (int w = 1; w <= THRESH; w ++) {
    // nlogn per operation
    memset(a, 0, sizeof a);
    for (int i = w; i <= M; i += w) a[i] = tab[i];
    Dft(a);
    for (int i = 0; i < N; i ++)
      a[i] = a[i] * a[i] % mod * a[i] % mod;
    Dft(a);
    ans = (ans + a[s] * IN % mod * phi[w]) % mod;
  }
  for (int w = THRESH + 1; w <= M; w ++) {
    LL cnt = 0;
    for (int i = w; i <= M; i += w)
      for (int j = w; j <= M; j += w)
        if ((i ^ j ^ s) % w == 0)
          (cnt += tab[i] * tab[j] * tab[i ^ j ^ s]) %= mod;
    ans = (ans + cnt * phi[w]) % mod;
  }
  for (int w = 1; w <= s; w ++)
    if (s % w == 0) {
      LL sub = 0, add = 0;
      for (int i = 0; i < N; i += w)
        if (i != s) {
          sub -= tab[i] * tab[i] * 3;
          add += tab[i] * (tab[i] - 1) / 2;
        }
      add = add % mod * tab[s] % mod;
      sub = (sub % mod + mod) * tab[s] % mod;
      sub -= tab[s] * tab[s] * tab[s];
      (add += tab[s] * (tab[s] - 1) * (tab[s] - 2) / 6) %= mod;
      sub = (sub % mod + mod) % mod;
      ans = (ans + (sub + add * 6) * phi[w]) % mod;
    }
  printf("%lld\n", ans * I6 % mod);
}

inline void solve4() {
  static LL a[N + 3];
  LL ans = 0;
  for (int w = 1; w <= THRESH; w ++) {
    // nlogn per operation
    memset(a, 0, sizeof a);
    for (int i = w; i <= M; i += w) a[i] = tab[i];
    Dft(a);
    for (int i = 0; i < N; i ++)
      a[i] = a[i] * a[i] % mod * a[i] % mod * a[i] % mod;
    Dft(a);
    ans = (ans + a[s] * IN % mod * phi[w]) % mod;
  }
  memset(a, 0, sizeof a);
  for (int w = THRESH + 1; w <= M; w ++) {
    LL cnt = 0;
    for (int i = w; i <= M; i += w)
      for (int j = w; j <= M; j += w)
        a[i ^ j] = (a[i ^ j] + tab[i] * tab[j]) % mod;
    for (int i = w; i <= M; i += w)
      for (int j = w; j <= M; j += w)
        (cnt += a[i ^ j ^ s] * tab[i] % mod * tab[j]) %= mod;
    for (int i = w; i <= M; i += w)
      for (int j = w; j <= M; j += w) a[i ^ j] = 0;
    ans = (ans + cnt * phi[w]) % mod;
  }
  for (int w = 1; w <= M; w ++) {
    LL sub = 0, add = 0, tot = 0, cr;
    for (int i = w; i <= M; i += w)
      if ((i ^ s) % w == 0) tot += (LL) tab[i] * tab[i ^ s];
    tot %= mod;
    for (int i = w, j; i <= M; i += w) {
      // aabc: b^c=s
      cr = tot * I2 % mod;
      j = i ^ s;
      if (j % w == 0)
        cr = cr - tab[i] * tab[j] % mod + mod;
      sub -= 12 * tab[i] * tab[i] % mod * cr % mod;
      add += cr % mod * (tab[i] * (tab[i] - 1) / 2 % mod) % mod;
      if (j % w == 0) {
        // aaab: a^b=s
        sub -= 4 * tab[i] * tab[i] * tab[i] % mod * tab[j] % mod;
        add += tab[i] * (tab[i] - 1) * (tab[i] - 2) / 6 % mod * tab[j] % mod;
      }
    }
    sub = (sub % mod + mod) % mod;
    add %= mod;
    ans = (ans + (sub + add * 24) * phi[w]) % mod;
  }
  printf("%lld\n", ans * I24 % mod);
}

int main() {
  freopen("choose.in", "r", stdin);
  freopen("choose.out", "w", stdout);
  scanf("%d%d%d", &n, &f, &s);
  for (int i = 1, a; i <= n; i ++) {
    scanf("%d", &a); tab[a] ++;
  }
  if (f == 1) {
    printf("%lld\n", tab[s] * s % mod);
    return 0;
  } else if (f == 2) {
    LL ans = 0;
    for (int i = 0; i < N; i ++)
      if (i > (s ^ i))
        (ans += (LL) tab[i] * tab[s ^ i] % mod * __gcd(i, s ^ i)) %= mod;
    printf("%lld\n", ans);
    return 0;
  } else {
    initPhi();
    if (f == 3) solve3();
    else solve4();
  }
  return 0;
}
