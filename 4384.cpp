#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
const int N = 1e5 + 50;
const int mod[] = { 998244353, (int)1e9 + 7 };

int val[2][17][N];
LL base[2][17];
int fa[N], tab[17][N], ch[N][26], n;
char ec[N], s[N];
int rnk[N], ord[N], dep[N];

inline int LCP(int x, int y) {
  if (!x || !y) return 0;
  x = ord[x]; y = ord[y];
  int ans = 0;
  for (int i = 16; ~ i; i --)
    if ( min(dep[x], dep[y]) >= (1 << i) &&
         val[0][i][x] == val[0][i][y] &&
         val[1][i][x] == val[1][i][y] ) {
      ans |= 1 << i;
      x = tab[i][x];
      y = tab[i][y];
    }
  return ans;
}

inline void Build() {
  static int buc[N], _buc[N], tmp[N], _rnk[N];
  int du = max(30, n);
  for (int i = 1; i <= n; i ++) rnk[i] = ec[i] - 'a' + 1;
  for (int t = 0; (1 << t) < n; t ++) {
    int *ta = tab[t];
    memset(buc, 0, sizeof(int) * (du + 1));
    memset(_buc, 0, sizeof(int) * (du + 1));
    for (int i = 1; i <= n; i ++) {
      buc[ rnk[i] ] ++;
      _buc[ rnk[ ta[i] ] ] ++;
    }
    for (int i = 1; i <= du; i ++) {
      buc[i] += buc[i - 1];
      _buc[i] += _buc[i - 1];
    }
    for (int i = 1; i <= n; i ++)
      tmp[_buc[ rnk[ ta[i] ] ] --] = i;
    for (int i = n, j = n + 1; i; i --)
      if (i == 1 || rnk[ ta[ tmp[i] ] ] != rnk[ ta[ tmp[i - 1] ] ]) {
        for (int k = i; k < j; k ++) _rnk[ tmp[k] ] = buc[ rnk[ tmp[k] ] ];
        for (int k = i; k < j; k ++) buc[ rnk[ tmp[k] ] ] --;
        j = i;
      }
    memcpy(rnk, _rnk, sizeof(int) * (n + 1));
  }
  for (int i = 1; i <= n; i ++) ord[rnk[i]] = i;
}

inline void print(int x) {
  for (; x; x = fa[x]) cerr << ec[x];
}

int main() {
  scanf("%s", s + 1);
  int p = 0;
  for (int i = 1; s[i]; i ++) {
    if (s[i] == '-') p = fa[p];
    else {
      if (!ch[p][s[i] - 'a']) {
        ch[p][s[i] - 'a'] = ++ n;
        fa[n] = tab[0][n] = p;
        ec[n] = s[i];
        dep[n] = dep[p] + 1;
      }
      p = ch[p][s[i] - 'a'];
    }
  }
  base[0][0] = base[1][0] = 27;
  for (int i = 1; i <= n; i ++)
    val[0][0][i] = val[1][0][i] = ec[i] - 'a' + 1;
  for (int j = 1; j < 17; j ++) {
    for (int i = 1; i <= n; i ++) {
      tab[j][i] = tab[j - 1][tab[j - 1][i]];
      for (int k = 0; k < 2; k ++)
        val[k][j][i] = ( val[k][j - 1][i] * base[k][j - 1]
                         + val[k][j - 1][tab[j - 1][i]] ) % mod[k];
    }
    for (int k = 0; k < 2; k ++)
      base[k][j] = base[k][j - 1] * base[k][j - 1] % mod[k];
  }
  Build();
  p = 0;
  set <int> d;
  long long ans = 0;
  for (int i = 1; s[i]; i ++) {
    if (s[i] == '-') {
      auto it = d.find(rnk[p]);
      int l = 0, r = 0;
      if (it != d.begin()) {
        it --; l = *it; it ++;
      }
      it ++;
      if (it != d.end()) r = *it;
      it --;
      d.erase(it);
      ans -= dep[p] - max( LCP(l, rnk[p]), LCP(r, rnk[p]) );
      p = fa[p];
    } else {
      p = ch[p][s[i] - 'a'];
      auto it = d.insert(rnk[p]).first;
      int l = 0, r = 0;
      if (it != d.begin()) {
        it --; l = *it; it ++;
      }
      it ++;
      if (it != d.end()) r = *it;
      ans += dep[p] - max( LCP(l, rnk[p]), LCP(r, rnk[p]) );
    }
    printf("%lld\n", ans);
  }
  return 0;
}
