#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

typedef long long LL;
const int N = 1e5 + 50;
const LL mod = 1e9 + 7;

vector <int> G[N], cir;
int n, a[N], sz, pt;
int vis[N], cur;
int len[N], cnt[N];
LL fac[N], inv[N];

inline void Dfs(int x) {
  if (vis[x]) {
    if (vis[x] != cur) sz = 0;
    else pt = x;
    return;
  }
  vis[x] = cur; sz ++;
  Dfs(a[x]);
}

inline void Dfs1(int x) {
  if (vis[x] == cur) return;
  cir.push_back(x);
  vis[x] = cur;
  Dfs1(a[x]);
}

inline int iDfs(int x) {
  if (G[x].size() > 1u) return (int) -1e9;
  if (!G[x].size()) return 1;
  return 1 + iDfs(G[x][0]);
}

inline LL Pow(LL x, LL exp) {
  LL r = 1;
  for (; exp; exp >>= 1, x = x * x % mod)
    if (exp & 1) r = r * x % mod;
  return r;
}

inline void Init() {
  for (int i = fac[0] = 1; i < N; i ++)
    fac[i] = fac[i - 1] * i % mod;
  inv[N - 1] = Pow(fac[N - 1], mod - 2);
  for (int i = N - 1; i; i --)
    inv[i - 1] = inv[i] * i % mod;
}

inline LL C(int x, int y) {
  return fac[x] * inv[y] % mod * inv[x - y] % mod;
}

int main() {
  Init();
  scanf("%d", &n);
  for (int i = 1; i <= n; i ++) {
    scanf("%d", &a[i]);
    G[a[i]].push_back(i);
  }
  LL res = 1;
  cir.reserve(n);
  for (int i = 1; i <= n; i ++)
    if (!vis[i]) {
      sz = 1; cur ++;
      Dfs(i); if (!sz) continue;
      cur ++; cir.clear();
      Dfs1(pt);
      reverse(cir.begin(), cir.end());
      int tot = 0, le = cir.size();
      for (int j = 0; j < le; j ++) {
        vector <int> &Gi = G[cir[j]];
        if (Gi.size() > 2u) return 0 * puts("0");
        if (Gi.size() == 1u) len[j + 1] = 0;
        else tot += (len[j + 1] = iDfs(Gi[vis[Gi[0]] == cur]));
        if (len[j + 1] < 0) return 0 * puts("0");
      }
      if (!tot) {
        cnt[le] ++; continue;
      }
      int dis = 0;
      for (int j = 1; j <= le; j ++)
        if (len[j]) {
          dis = j - 1; break;
        }
      for (int j = le; j; j --) {
        dis ++;
        if (!len[j]) continue;
        if (dis > len[j]) {
          res <<= 1;
          if (res >= mod) res -= mod;
        }
        else if (dis < len[j]) return 0 * puts("0");
        dis = 0;
      }
    }
  for (int i = 1; i <= n; i ++) {
    if (!cnt[i]) continue;
    LL t = ((i & 1) && i != 1) + 1;
    LL tmp = Pow(t, cnt[i]);
    for (int j = (cnt[i] >> 1); j; j --)
      tmp += C(cnt[i], j << 1) * C(j << 1, j) % mod * Pow((mod + 1) >> 1, j) % mod * fac[j] % mod * Pow(i, j) % mod * Pow(t, (LL) cnt[i] - (j << 1)) % mod;
    res = res * (tmp % mod) % mod;
  }
  printf("%lld\n", res);
  return 0;
}
