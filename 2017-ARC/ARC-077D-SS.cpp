#include <cstdio>
#include <iostream>
#include <cstring>
using namespace std;

typedef long long LL;
const int N = 2e5 + 5;

char s[N];
int fail[N], n, cyc;
LL l, r, add[27], sub[27], tots[27], tott[27];
LL tab[90], cnts[90], cntt[90];

inline void solve1() {
  for (int i = 1; i <= cyc; i ++) add[s[i] - 'a'] ++;
  for (int i = 0; i < 26; i ++) {
    sub[i] = add[i] * (l / cyc);
    add[i] *= r / cyc;
  }
  for (int i = 1; i <= l % cyc; i ++) sub[s[i] - 'a'] ++;
  for (int i = 1; i <= r % cyc; i ++) add[s[i] - 'a'] ++;
}

inline void dfs(LL x, LL *res) {
  if (x <= n) {
    for (int i = 1; i <= x; i ++) res[s[i] - 'a'] ++;
    return;
  }
  int p;
  for (p = 1; tab[p + 1] <= x; p ++);
  for (int i = 0; i < 26; i ++) res[i] += cnts[p] * tots[i] + cntt[p] * tott[i];
  dfs(x - tab[p], res);
}

inline void solve2() {
  tab[0] = cyc; tab[1] = n;
  cnts[1] = 1;
  cntt[0] = 1;
  for (int i = 1; tab[i] <= r; i ++) {
    tab[i + 1] = tab[i] + tab[i - 1];
    cnts[i + 1] = cnts[i] + cnts[i - 1];
    cntt[i + 1] = cntt[i] + cntt[i - 1];
  }
  for (int i = 1; i <= n; i ++) tots[s[i] - 'a'] ++;
  for (int i = 1; i <= cyc; i ++) tott[s[i] - 'a'] ++;
  dfs(l, sub);
  dfs(r, add);
}

int main() {
  scanf("%s", s + 1);
  scanf("%lld%lld", &l, &r);
  l --;
  n = strlen(s + 1) >> 1;
  for (int i = 2, j = 0; i <= n; i ++) {
    while (j && s[j + 1] != s[i]) j = fail[j];
    if (s[i] == s[j + 1]) fail[i] = ++ j;
    else fail[i] = j;
  }
  cyc = n - fail[n];
  if (n % cyc == 0) solve1();
  else solve2();
  LL tot = 0;
  for (int i = 0; i < 26; i ++) {
    printf("%lld ", add[i] - sub[i]);
    tot += add[i] - sub[i];
  }
  return 0;
}
