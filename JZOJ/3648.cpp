#include <bits/stdc++.h>
using namespace std;

const int N = 2e6 + 50;

int n;

inline void calc(char *s, char *t, int *ans) {
  static int ext[N];
  int p = 0, a = 0;
  s[n + 1] = '+';
  t[n + 1] = '-';
  ext[1] = n;
  for (int k = 2, L; k <= n; ++ k) {
    if (p < k) {
      ext[k] = 0;
      for (; t[ext[k] + k] == t[ext[k] + 1]; ++ ext[k]);
      a = k; p = k + ext[k] - 1;
      continue;
    }
    L = ext[k - a + 1];
    if (L > p - k + 1) ext[k] = p - k + 1;
    else {
      ext[k] = L;
      for (; t[ext[k] + k] == t[ext[k] + 1]; ++ ext[k]);
      a = k; p = k + ext[k] - 1;
    }
  }
  a = p = 0;
  for (int k = 1, L; k <= n; ++ k) {
    if (p < k) {
      ans[k] = 0;
      for (; s[ans[k] + k] == t[ans[k] + 1]; ++ ans[k]);
      a = k; p = k + ans[k] - 1;
      continue;
    }
    L = ext[k - a + 1];
    if (L > p - k + 1) ans[k] = p - k + 1;
    else {
      ans[k] = L;
      for (; s[ans[k] + k] == t[ans[k] + 1]; ++ ans[k]);
      a = k; p = k + ans[k] - 1;
    }
  }
}

char s[N], t[N];
int a[N], b[N], fa[N];

struct edge {
  int nxt, to;
} e[N];
int fir[N], cnt = 1;

inline void addedge(int x, int y) {
  e[++ cnt] = (edge) { fir[x], y }; fir[x] = cnt;
}

inline int getf(int x) { return fa[x] == x ? x : fa[x] = getf(fa[x]); }

int main() {
  scanf("%d", &n);
  scanf("%s", s + 1);
  scanf("%s", t + 1);
  calc(s, t, a);
  calc(t, s, b);
  for (int i = 1; i <= n; ++ i) {
    fa[i] = i;
    addedge(a[i], i);
  }
  int ans = 0;
  for (int i = 1, v; i <= n; ++ i) {
    v = getf(b[i] + 1);
    if (v) ans = max(ans, v - 1 + i - 1);
    for (int j = fir[i - 1]; j; j = e[j].nxt) fa[e[j].to] = e[j].to - 1;
  }
  printf("%d\n", ans);
  return 0;
}
