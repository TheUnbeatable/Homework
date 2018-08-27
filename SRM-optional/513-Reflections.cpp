#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
typedef vector <int> vi;

class Reflections {
private :
  LL res;
  set <LL> rec[30][11];
  int a[30], n, term, half;
  inline LL mabs(LL x) { return max(x, - x); }
  inline LL minSum(set <LL> &s, LL val) {
    if (!s.size()) return (LL)9e18;
    set <LL> :: iterator it = s.lower_bound(val);
    LL ret = 9e18;
    if (it != s.end())
      ret = mabs(val - *it);
    if (it != s.begin()) {
      it --;
      ret = min(ret, mabs(val - *it));
    }
    return ret;
  }
  inline void Dfs1(int x, int sgn, int cnt, LL sum) {
    if (x > half)
      return (void) rec[sgn][cnt].insert(sum);
    Dfs1(x + 1, sgn, cnt, sum);
    Dfs1(x + 1, sgn + 1, cnt + 1, sum + a[x]);
    Dfs1(x + 1, sgn - 1, cnt + 1, sum - a[x]);
  }
  inline void Dfs2(int x, int sgn, int cnt, LL sum) {
    if (x > n) {
      for (int i = 0; i <= half; i ++)
	res = min( res, min( minSum(rec[24 - sgn][i], term - sum),
			     minSum(rec[25 - sgn][i], term - sum) ) + i + cnt );
      return;
    }
    Dfs2(x + 1, sgn, cnt, sum);
    Dfs2(x + 1, sgn + 1, cnt + 1, sum + a[x]);
    Dfs2(x + 1, sgn - 1, cnt + 1, sum - a[x]);
  }
public :
  inline void Solve() {
    for (int i = 0; i < 30; i ++)
      for (int j = 0; j < 11; j ++) rec[i][j].clear();
    res = 9e18;
    half = n >> 1;
    Dfs1(1, 12, 0, 0);
    Dfs2(half + 1, 12, 0, 0);
  }
  inline LL minimumMoves(vi mirrorX, vi mirrorY, vi mirrorZ, vi finalPosition) {
    LL ans = 0;
    n = mirrorX.size(); term = finalPosition[0];
    for (int i = 0; i < n; i ++) a[i + 1] = mirrorX[i] << 1;
    Solve(); ans += res;
    n = mirrorY.size(); term = finalPosition[1];
    for (int i = 0; i < n; i ++) a[i + 1] = mirrorY[i] << 1;
    Solve(); ans += res;
    n = mirrorZ.size(); term = finalPosition[2];
    for (int i = 0; i < n; i ++) a[i + 1] = mirrorZ[i] << 1;
    Solve(); ans += res;
    return ans;
  }
};
