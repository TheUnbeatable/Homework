#pragma GCC optimize("3")
#pragma GCC optimize("inline")
#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
const int N = 1e5 + 50;
const int mod = 998244353;

int n, a[N], tab[N];
unordered_map <LL, int> sum, _sum;
unordered_map <LL, LL> pi;
bool notp[N], vis[N];
vector <int> di[N];
vector <pair <int, int> > part[4];

inline void Init() {
  for (int i = 2; i <= n; i ++)
    if (!notp[i]) {
      for (int j = i; j <= n; j += i) {
        notp[j] = 1;
        di[j].push_back(i);
      }
    }
}

int sta[N], cnt[N], top;

inline void Inc(int &x, int y) { if ((x += y) >= mod) x -= mod; }

inline void Dfs(int x, LL prod, LL phi, int val, bool fi) {
  if (x > top) {
    pi[prod] = phi;
    if (fi) Inc(sum[prod], val);
    else Inc(_sum[prod], val);
    return;
  }
  Dfs(x + 1, prod, phi, val, fi);
  for (int i = 1; i <= cnt[x]; i ++) {
    prod *= sta[x];
    Dfs(x + 1, prod, phi * (sta[x] - 1), val, fi);
    phi *= sta[x];
  }
}

int main() {
  freopen("space.in", "r", stdin);
  freopen("space.out", "w", stdout);
  sum.rehash(3000007);
  _sum.rehash(3000007);
  pi.rehash(3000007);
  scanf("%d", &n); Init();
  for (int w = 0; w < 4; w ++) {
    for (int i = 1; i <= n; i ++) scanf("%d", &a[i]);
    memset(vis, 0, sizeof vis);
    memset(tab, 0, sizeof tab);
    for (int i = 1; i <= n; i ++)
      if (!vis[i]) {
        int tot = 0;
        for (int j = i; !vis[j]; j = a[j]) vis[j] = 1, tot ++;
        tab[tot] ++;
      }
    for (int i = 1; i <= n; i ++)
      if (tab[i]) part[w].push_back(make_pair(i, tab[i]));
  }
  int x, y, c, d;
  map <int, int> tmp;
  for (int w = 0; w < 2; w ++)
    for (auto i : part[w * 2])
      for (auto j : part[w * 2 + 1]) {
        x = i.first; c = i.second;
        y = j.first; d = j.second;
        tmp.clear();
        int q = x;
        for (auto u : di[x]) {
          int &p = tmp[u];
          for (; q % u == 0; q /= u) p ++;
        }
        q = y / __gcd(x, y);
        int ttt = q;
        for (auto u : di[ttt]) {
          int &p = tmp[u];
          for (; q % u == 0; q /= u) p ++;
        }
        top = 0;
        for (auto u : tmp) {
          sta[++ top] = u.first;
          cnt[top] = u.second;
        }
        Dfs(1, 1, 1, 1ll * c * d * __gcd(x, y) % mod, w);
      }
  LL ans = 0;
  for (auto i : sum)
    (ans += pi[i.first] % mod * i.second % mod * _sum[i.first]) %= mod;
  LL u = 1ll * n * n % mod;
  ans = (u * u + ans) % mod;
  printf("%lld\n", ans);
  return 0;
}
