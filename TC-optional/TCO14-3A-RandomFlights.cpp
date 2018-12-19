#include <bits/stdc++.h>
using namespace std;

const int N = 18;

class RandomFlights {
private:
  int n, msk[N], bit[1 << N], cnt[N];
  double dis[N][N], dp[1 << N], pos[1 << N];
  double G[N][N], sum[N], sumdis[N][1 << 9], _sumdis[N][1 << 9];
  inline double sqr(double x) { return x * x; }
  inline double bf(int x, int s, int BEG) {
    s <<= BEG;
    double res = 0;
    for (int i = BEG; i < BEG + 9; i ++)
      if ((s >> i) & 1) res += dis[x][i];
    return res;
  }
  inline double calc(int x, int s) {
    return sumdis[x][s & 511] + _sumdis[x][s >> 9];
  }
public:
  inline double expectedDistance(vector <int> x, vector <int> y, vector <string> flight){
    memset(cnt, 0, sizeof cnt);
    memset(msk, 0, sizeof msk);
    memset(pos, 0, sizeof pos);
    memset(dp, 0, sizeof dp);
    memset(sum, 0, sizeof sum);
    memset(msk, 0, sizeof msk);
    memset(dis, 0, sizeof dis);
    n = x.size();
    for (int i = 0; i < n; i ++)
      for (int j = 0; j < n; j ++)
        dis[i][j] = sqrt( sqr(x[i] - x[j]) + sqr(y[i] - y[j]) );
    memcpy(G, dis, sizeof G);
    for (int i = 0; i < n; i ++)
      for (int j = 0; j < n; j ++) {
        if (flight[i][j] == '1' || i == j) ;
        else G[i][j] = 1e20;
      }
    for (int i = 0; i < n; i ++)
      for (int j = 0; j < (1 << 9); j ++) sumdis[i][j] = bf(i, j, 0);
    for (int i = 0; i < n; i ++)
      for (int j = 0; j < (1 << 9); j ++) _sumdis[i][j] = bf(i, j, 9);
    for (int k = 0; k < n; k ++)
      for (int i = 0; i < n; i ++)
        for (int j = 0; j < n; j ++)
          G[i][j] = min(G[i][j], G[i][k] + G[k][j]);
    for (int i = 0; i < n; i ++)
      for (int j = 0; j < n; j ++)
        if (G[i][j] < 1e20) {
          sum[i] += G[i][j];
          msk[i] |= 1 << j;
          cnt[i] ++;
        }
    if (msk[0] & 2) return G[0][1];
    bit[0] = 0;
    for (int i = 1; i < (1 << n); i ++)
      bit[i] = bit[i >> 1] + (i & 1);
    double ans = 0;
    pos[msk[0]] = 1;
    dp[msk[0]] = sum[0] / cnt[0];
    for (int i = msk[0] + 2, k; i < (1 << n); i += 2) {
      if ((i & msk[0]) != msk[0]) continue;
      double &p = pos[i];
      double s = 0;
      int rem = n - bit[i], done = bit[i];
      for (int j = 1; j < n; j ++)
        if ((msk[j] & i) == msk[j] && msk[j] != i) {
          k = i ^ msk[j];
          p += pos[k] / (rem + cnt[j]);
          s += (dp[k] + (sum[j] + calc(j, k) / bit[k] * cnt[j]) / done) * pos[k] / (rem + cnt[j]);
          if (msk[j] & 2) ans += pos[k] / (rem + cnt[j]) * (G[j][1] + dp[k] + calc(j, k) / bit[k]);
        }
      if (p) dp[i] = s / p;
    }
    return ans;
  }
};
