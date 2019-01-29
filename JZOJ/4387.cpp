#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 50;
const char cset[] = { 'A', 'T', 'G', 'C' };

char s[N];
int ch[N][4], Min[N], fail[N], len[N], dir[N], half[N], dp[N], lst, Sz;
map <char, int> trans;

inline int getFail(int p, int n) {
  for (; s[n - len[p] - 1] != s[n]; p = fail[p]);
  return p;
}

int n;

inline void Init() {
  memset(ch, 0, sizeof ch);
  memset(fail, 0, sizeof fail);
  memset(len, 0, sizeof len);
  Sz = 1;
  len[1] = -1; len[0] = 0;
  fail[0] = 1;
  lst = 1;
}

inline void solve() {
  Init();
  scanf("%s", s + 1);
  n = strlen(s + 1);
  for (int i = 1, c; i <= n; ++ i) {
    c = trans[s[i]];
    int p = getFail(lst, i);
    if (!ch[p][c]) {
      ++ Sz;
      dir[Sz] = p;
      len[Sz] = len[p] + 2;
      fail[Sz] = ch[getFail(fail[p], i)][c];
      ch[p][c] = Sz;
      if (!(len[Sz] & 1)) {
        int q = getFail(half[p], i);
        if (len[q] + 2 > len[Sz] / 2) q = getFail(fail[q], i);
        half[Sz] = ch[q][c];
      }
    }
    lst = ch[p][c];
  }
  int ans = n;
  dp[0] = dp[1] = 0;
  for (int i = 2; i <= Sz; ++ i) {
    if (len[i] <= 2) dp[i] = len[i];
    else if (len[i] & 1) dp[i] = len[i];
    else dp[i] = min(1 + dp[dir[i]], Min[half[i]] + 1 + len[i] / 2);
    Min[i] = min(Min[fail[i]], dp[i] - len[i]);
    ans = min(ans, n - len[i] + dp[i]);
  }
  printf("%d\n", ans);
}

int main() {
  for (int i = 0; i < 4; ++ i) trans[cset[i]] = i;
  int T; scanf("%d", &T);
  while (T --) solve();
  return 0;
}
