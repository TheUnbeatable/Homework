#include <cstdio>
#include <iostream>
#include <vector>
#include <string>
#include <cstring>
using namespace std;

typedef long long LL;
const int N = 140;
const int W = 12;

class KingdomXEmergencyStaircase {
private :
  LL dp[3][N][W][W][W];
  int prel[N], prer[N];
  vector <int> C;
  inline LL DP(int t, int h, int h1, int h2, int h3) {
    //1 -2 1 3 2
    if (dp[t][h][h1][h2][h3] != -1) return dp[t][h][h1][h2][h3];
    int h4 = h - h1 + h2 + h3 - (h1 + h2 - h3);
    LL ans = 1e18;
    if (t == 0 || t == 1) {//Mid
      if (t == 0 && prel[h4 - 1] - prel[h] <= 0)
        return dp[t][h][h1][h2][h3] = 0;
      if (t == 1 && prer[h4 - 1] - prer[h] <= 0)
        return dp[t][h][h1][h2][h3] = 0;
      for (int i = 1; i <= h1; i ++)
        ans = min(ans, DP(t, h, h1 - i, h2, h3 - i) + C[h2]);
      for (int i = 2; i < h4 - h; i += 2)
        ans = min(ans, DP(t, h + i, 0, h2 - i / 2, h3 - i / 2 - h1)
                  + DP(t, h, h1, h2, h1 + i / 2) + C[h2 - i / 2]);
      for (int i = 1; i <= h1 + h2 - h3; i ++)
        ans = min(ans, DP(t, h, h1, h2 - i, h3) + C[h3]);
      for (int i = 2; i < h4 - h; i += 2)
        ans = min(ans, DP(t, h + i, h1 + i / 2, h2 - i / 2, h3)
                  + DP(t, h, h1, i / 2, h1 + i / 2) + C[h1 + i / 2]);  
    }
    else {//Up
      int l = h - h1 + h2;
      if (prel[h] == prel[N - 1] && prer[l] == prer[N - 1]) return dp[t][h][h1][h2][h3] = 0;
      for (int i = 1; i <= h1; i ++)
        ans = min(ans, DP(t, h, h1 - i, h2 + i, 0)
                  + DP(1, l, h2, i, h2 + i) + C[h2 + i]);
      for (int i = 1; i <= h2; i ++)
        ans = min(ans, DP(t, h + 2 * i, h1 + i, h2 - i, 0)
                  + DP(0, h, h1, i, h1 + i) + C[h1 + i]);
    }
    return dp[t][h][h1][h2][h3] = ans;
  }
public :
  inline LL determineCost(string lt, string rt, vector <int> cost) {
    C.push_back(0); for (auto i : cost) C.push_back(i);
    memset(dp, -1, sizeof dp);
    memset(prel, 0, sizeof prel);
    memset(prer, 0, sizeof prer);
    int wid = cost.size();
    for (int i = 0; i < (int)lt.length(); i ++)
      if (lt[i] == 'Y') prel[(i + 1) << 1] ++;
    for (int i = 0; i < (int)rt.length(); i ++)
      if (rt[i] == 'Y') prer[(i + 1) << 1] ++;
    for (int i = 1; i < N; i ++)
      prel[i] += prel[i - 1], prer[i] += prer[i - 1];
    LL ans = 1e18, tmp;
    tmp = DP(2, 0, 0, wid, 0);
    for (int i = 0; i <= wid; i += 2) {
      ans = min(ans, tmp + DP(1, i, 0, (wid - i) / 2, (wid - i) / 2) + C[(wid - i) / 2]);
      if (prer[i]) break;
    }
    tmp = DP(2, wid, wid, 0, 0);
    for (int i = 0; i <= wid; i += 2) {
      ans = min(ans, tmp + DP(0, i, 0, (wid - i) / 2, (wid - i) / 2) + C[(wid - i) / 2]);
      if (prel[i]) break;
    }
    ans += C[wid];
    return ans;
  }
} solver;
