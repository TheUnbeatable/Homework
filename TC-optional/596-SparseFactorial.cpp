#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
#define FOR(it, v) for (vector <int> :: iterator it = v.begin(); it != v.end(); it ++)
using namespace std;

typedef long long LL;
const int N = 1e6 + 50;

class SparseFactorial {
private:
  int mo;
  LL res[N];
  vector <int> buc[N];
  
  inline void update(int p, int exp) {
    for (int i = 0; i < p; i ++) buc[i].clear();
    for (int i = 0; i < mo; i ++)
      buc[1ll * i * i % p].push_back(i);
    for (int i = 0; i < mo; i ++) {
      if (res[i] == 1e18) continue;
      vector <int> &b = buc[i % p];
      int cnt = 0;
      FOR(it, b) {
        int x = (i - 1ll * (*it) * (*it) % mo + mo) % mo;
        while (cnt < exp && x % p == 0) {
          x /= p; cnt ++;
        }
        if (cnt == exp) {
          res[i] = max(res[i], 1ll * (*it) * (*it));
          break;
        }
      }
      if (cnt != exp) res[i] = 1e18;
    }
  }
public:
  inline LL getCount(LL lo, LL hi, LL divisor) {
    mo = divisor;
    memset(res, 0, sizeof(LL) * divisor);
    for (int i = 2; i * i <= divisor; i ++)
      if (divisor % i == 0) {
        int exp = 0;
        while (divisor % i == 0) {
          divisor /= i; exp ++;
        }
        update(i, exp);
      }
    if (divisor > 1) update(divisor, 1);
    LL ans = 0;
    lo --;
    for (int i = 0; i < mo; i ++)
      if (res[i] <= hi) ans += (hi + mo - i) / mo - (max(lo, res[i]) + mo - i) / mo;
    return ans;
  }
};
