#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;

typedef long long LL;
const int N = 55;

LL mod;

class ModuloCounters {
private:
  int n;
  struct node {
    LL a, k;
    node(LL _a = 0, LL _k = 0): a(_a), k(_k) {}
    inline node operator - (const node &o) {
      return node((a - o.a + mod) % mod, k - o.k);
    }
    inline node operator + (const node &o) {
      return node(a + o.a, k + o.k);
    }
    inline LL calc(LL x) {
      return (a + x * k + mod) % mod;
    }
  } d[N][3];
  inline LL calc(node p) {
    LL x = (mod - p.a * p.k) % mod;
    LL res = d[0][1].calc(x) + d[0][2].calc(x);
    for (int i = 1; i <= n; i ++)
      res = max(res, d[i][1].calc(x) + d[i][2].calc(x) + d[i - 1][2].calc(x));
    return res;
  } 
public:
  inline LL minFoxes(LL M, vector <LL> counter) {
    mod = M; n = counter.size();
    counter.insert(counter.begin(), 0);
    d[0][1] = node(counter[1], 0);
    d[0][2] = node(M - counter[1], 1);
    for (int i = 1; i < n; i ++) {
      d[i][1] = node(counter[i + 1], 0) - d[i - 1][2];
      d[i][2] = node(counter[i], 0) - d[i][1];
    }
    d[n][1] = node(0, 1) - d[n - 1][2];
    LL ans = 1e18;
    for (int i = 0; i <= n; i ++)
      ans = min( ans, min( calc(d[i][1]), calc(d[i][2]) ) );
    return ans;
  }
};
