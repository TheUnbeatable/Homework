#include <bits/stdc++.h>
using namespace std;

const int N = 2510;

class BrightLamps {
private:
  int cnt[N], sum[N], mn[N];
public:
  inline int maxBrightness(string init, vector <int> a, int K) {
    memset(cnt, 0, sizeof cnt);
    memset(sum, 0, sizeof sum);
    memset(mn, 0x3f, sizeof mn);
    int n = init.length();
    for (int i = 0; i < n; i ++) {
      cnt[i % K] ^= (init[i] == '0');
      sum[i % K] += a[i];
      mn[i % K] = min(mn[i % K], a[i]);
    }
    int ans = 0;
    for (int i = 0; i < 2; i ++) {
      int res = 0;
      for (int j = 0; j < K; j ++)
        res += sum[j] - (i == cnt[j] ? 0 : mn[j]);
      ans = max(ans, res);
    }
    return ans;
  }
};
