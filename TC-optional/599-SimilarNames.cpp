#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <map>
#include <string>
#include <vector>
using namespace std;

const int N = 52;
const int mod = 1e9 + 7;

class SimilarNames {
private:
  int id[N], wh[N], m, n;
  vector <int> G[N];
  int dp[N][1 << 16 | 3], term[17], swp[1 << 16 | 3];
  inline void Merge(int x, int y) {
    int *p = dp[x];
    int *q = dp[y];
    memset(swp, 0, sizeof swp);
    for (int i = 0, o; i < (1 << m); i ++)
      if (p[i]) {
        o = (1 << m) - 1;
        o ^= i;
        for (int j = o; ; j = (j - 1) & o) {
          if (q[j]) swp[i | j] = (swp[i | j] + 1ll * p[i] * q[j]) % mod;
          if (!j) break;
        }
      }
    memcpy(dp[x], swp, sizeof swp);
  }
  inline void Dfs(int x) {
    memset(dp[x], 0, sizeof dp[x]);
    dp[x][0] = 1;
    for (size_t i = 0; i < G[x].size(); i ++) {
      Dfs(G[x][i]);
      if (!i) memcpy(dp[x], dp[G[x][i]], sizeof dp[x]);
      else Merge(x, G[x][i]);
    }
    if (x == n) return;
    memcpy(swp, dp[x], sizeof swp);
    int *f = dp[x];
    for (int i = 0, o, p, q; i < m; i ++) {
      o = (1 << m) - 1;
      q = term[i];
      p = q | (1 << i);
      o ^= p;
      for (int j = o; ; j = (j - 1) & o) {
        swp[j | p] += (swp[j | p] + f[j | q] >= mod ? f[j | q] - mod : f[j | q]);
        if (!j) break;
      }
    }
    memcpy(dp[x], swp, sizeof swp);
  }
public:
  inline int count(vector<string> names, vector<int> info1, vector<int> info2) {
    memset(id, -1, sizeof id); m = -1;
    for (size_t i = 0; i < info1.size(); i ++) {
      if (id[info1[i]] == -1) id[info1[i]] = ++ m;
      if (id[info2[i]] == -1) id[info2[i]] = ++ m;
      term[id[info1[i]]] |= 1 << id[info2[i]];
    }
    m ++;
    for (int i = 0; i < n; i ++) wh[id[i]] = i;
    n = names.size();
    map <string, int> rec;
    rec[""] = n;
    for (int i = 0; i < n; i ++) rec[names[i]] = i;
    for (int i = 0; i < n; i ++) {
      string s = names[i];
      s.erase((int)s.length() - 1);
      while (!rec.count(s))
        s.erase((int)s.length() - 1);
      G[rec[s]].push_back(i);
    }
    Dfs(n);
    long long oth = 1;
    for (int i = 1; i <= n - m; i ++) oth = oth * i % mod;
    return (int)( dp[n][(1 << m) - 1] * oth % mod );
  }
};
