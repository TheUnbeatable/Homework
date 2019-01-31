#include <bits/stdc++.h>
using namespace std;

const int N = 1e6 + 50;
const int mod = 1e9 + 7;
const int base = 1e5 + 13;

int ch[N][10], fa[N], pos[N], Max[N], Sz = 1, lst = 1;

inline void append(int c, int loc) {
  int p = lst;
  int np = lst = ++ Sz;
  pos[np] = loc;
  Max[np] = Max[p] + 1;
  for (; p && !ch[p][c]; p = fa[p]) ch[p][c] = np;
  if (!p) fa[np] = 1;
  else {
    int q = ch[p][c];
    if (Max[q] == Max[p] + 1) fa[np] = q;
    else {
      int nq = ++ Sz;
      memcpy(ch[nq], ch[q], sizeof ch[q]);
      fa[nq] = fa[q];
      fa[np] = fa[q] = nq;
      pos[nq] = pos[q];
      Max[nq] = Max[p] + 1;
      for (; ch[p][c] == q; p = fa[p]) ch[p][c] = nq;
    }
  }
}

struct edge {
  int nxt, to;
} e[N];
int fir[N], cnt = 1;
long long d[N], dd[N];
int L[N], R[N];
int n;
char s[N];

inline void add(int l, int r, int v) { d[l] += v; d[r + 1] -= v; }

inline void sub(int l, int r) {
  dd[l] --; dd[r + 1] ++; d[r + 1] += r - l + 1;
}

inline void addedge(int x, int y) {
  e[++ cnt] = (edge) { fir[x], y }; fir[x] = cnt;
}

inline void Dfs(int x) {
  L[x] = R[x] = pos[x];
  for (int i = fir[x]; i; i = e[i].nxt) {
    Dfs(e[i].to);
    L[x] = min(L[x], L[e[i].to]);
    R[x] = max(R[x], R[e[i].to]);
  }
  if (x == 1) return;
  int p = R[x] - Max[x] + 1;
  int q = R[x] - (Max[fa[x]] + 1) + 1;
  // cerr << "!!!!!!!!!!" << endl;
  // cerr << pos[x] << ": " << L[x] << " " << R[x] << " / " << p << " " << q << endl;
  // for (int i = p; i <= q; i ++) {
  //   for (int j = i; j <= R[x]; j ++) putchar(s[j]);
  //   puts("");
  // }
  int delta = q - p + 1;
  if (q <= L[x]) {
    add(1, q, delta);
    add(L[x], n, delta);
    sub(p, q);
  } else if (p <= L[x]) {
    add(1, n, delta);
    sub(p, L[x] - 1);
  } else add(1, n, delta);
}

int main() {
  scanf("%d", &n);
  scanf("%s", s + 1);
  for (int i = 1; i <= n; i ++)
    append(s[i] - '0', i);
  for (int i = 2; i <= Sz; i ++) addedge(fa[i], i);
  Dfs(1);
  for (int i = 1; i <= n; i ++)
    dd[i] += dd[i - 1], d[i] += dd[i];
  long long ans = 0;
  for (int i = 1; i < n; i ++) {
    d[i] += d[i - 1];
    ans = (ans * base + d[i]) % mod;
    // cerr << d[i] << " ";
  }
  printf("%lld\n", ans);
  return 0;
}
