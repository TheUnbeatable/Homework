#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

int w;

class AlwaysDefined {
private:
  vector <int> valid[3010];
  inline LL Count(int rem, LL bnd, int mod = w) {
    if (rem > bnd) return 0;
    return (bnd - rem) / mod + 1;
  }
  inline LL solve(int rem, LL cnt) {
    if (rem == 1 || cnt <= 1) return cnt;
    LL res = 0;
    int i, nw;
    for (vector <int> :: iterator it = valid[rem].begin(); it != valid[rem].end(); it ++) {
      i = *it;
      nw = i * w / rem + 1;
      LL t = Count(i, cnt - 1, rem);
      if (!t) break;
      res += solve(nw, t);
    }
    return res;
  }
public:
  inline LL countIntegers(LL L, LL R, int _w) {
    w = _w; L --;
    for (int i = 1; i < w; i ++) {
      valid[i].clear();
      for (int j = 0; j < i; j ++)
        if (j * w % i == 0) valid[i].push_back(j);
    }
    LL ans = 0;
    for (int i = 1; i < w; i ++)
      ans += solve(i, Count(i, R)) - solve(i, Count(i, L));
    return ans;
  }
};
