#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <sstream>
#include <algorithm>
using namespace std;

typedef long long LL;
typedef vector <string> vs;
const int N = 152;

LL dp[N][N][N];
int a[N], b[N], c[N];
int ida[N], idb[N], idc[N];
int ra[N], rb[N], rc[N];
inline bool cmpa(int i, int j) { return a[i] < a[j]; }
inline bool cmpb(int i, int j) { return b[i] < b[j]; }
inline bool cmpc(int i, int j) { return c[i] < c[j]; }

class SlimeXSlimeRancher {
private :
  int n;
  inline void Init(vs fi, vs se, vs th) {
    n = 0; string s = "";
    for (size_t i = 0; i < fi.size(); i ++) s += fi[i];
    stringstream ss(s);
    while (ss >> a[++ n]); n --;
    s = ""; for (size_t i = 0; i < se.size(); i ++) s += se[i];
    stringstream tt(s); for (int i = 1; i <= n; i ++) tt >> b[i];
    s = ""; for (size_t i = 0; i < th.size(); i ++) s += th[i];
    stringstream vv(s); for (int i = 1; i <= n; i ++) vv >> c[i];
  }
public :
  inline LL train(vs fi, vs se, vs th) {
    Init(fi, se, th);
    memset(dp, 0, sizeof dp);
    for (int i = 1; i <= n; i ++)
      ida[i] = idb[i] = idc[i] = i;
    sort(ida + 1, ida + n + 1, cmpa);
    sort(idb + 1, idb + n + 1, cmpb);
    sort(idc + 1, idc + n + 1, cmpc);
    for (int i = 1; i <= n; i ++)
      ra[ida[i]] = rb[idb[i]] = rc[idc[i]] = i;
    for (int i = 1; i <= n; i ++)
      for (int j = 1; j <= n; j ++)
        for (int k = 1; k <= n; k ++) {
          LL res = 9e18;
          if (rb[ida[i]] <= j && rc[ida[i]] <= k)
            res = min(res, dp[i - 1][j][k] - b[ida[i]] + b[idb[j]] - c[ida[i]] + c[idc[k]]);
          else res = min(res, dp[i - 1][j][k]);
          if (ra[idb[j]] <= i && rc[idb[j]] <= k)
            res = min(res, dp[i][j - 1][k] - a[idb[j]] + a[ida[i]] - c[idb[j]] + c[idc[k]]);
          else res = min(res, dp[i][j - 1][k]);
          if (ra[idc[k]] <= i && rb[idc[k]] <= j)
            res = min(res, dp[i][j][k - 1] - a[idc[k]] + a[ida[i]] - b[idc[k]] + b[idb[j]]);
          else res = min(res, dp[i][j][k - 1]);
          dp[i][j][k] = res;
        }
    return dp[n][n][n];
  }
};
