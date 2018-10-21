#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;

const int N = 16;

class AntlerSwapping {
private:
  int dp[1 << N | 5];
  vector <int> cur;
  inline int diff(int x, int y) {
    return x > y ? x - y : y - x;
  }
public:
  inline int getmin(vector <int> antler1, vector <int> antler2, int capacity) {
    int n = antler1.size();
    cur.reserve(n << 1);
    dp[0] = 0;
    for (int i = 1; i < (1 << n); i ++) {
      int &tot = dp[i] = 0;
      cur.clear();
      for (int j = 0; j < n; j ++)
        if ((i >> j) & 1) {
          tot ++;
          cur.push_back(antler1[j]);
          cur.push_back(antler2[j]);
        }
      tot --;
      sort(cur.begin(), cur.end());
      for (size_t j = 0; j < cur.size(); j ++)
        if (diff(cur[j], cur[j ^ 1]) > capacity) tot = 1e9;
    }
    for (int i = 1; i < (1 << n); i ++) {
      int &c = dp[i];
      for (int j = i; j; j = (j - 1) & i)
        c = min(c, dp[j] + dp[i ^ j]);
    }
    int ans = dp[(1 << n) - 1];
    if (ans >= n) return -1;
    return ans;
  }
};
