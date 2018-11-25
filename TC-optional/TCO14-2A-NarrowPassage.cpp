#include <bits/stdc++.h>
using namespace std;

const int N = 55;

class NarrowPassage {
private:
  pair <int, int> p[N];
  int des[N];
  inline int mabs(int x) { return max(x, -x); }
public:
  int minDist(int L, vector <int> a, vector <int> b) {
    int n = a.size();
    for (int i = 0; i < n; i ++) p[i + 1] = make_pair(a[i], b[i]);
    sort(p + 1, p + n + 1);
    for (int i = 1; i <= n; i ++) {
      des[i] = 0; 
      for (int j = 1; j <= n; j ++)
        des[i] += (p[j].second <= p[i].second);
    }
    int ans = 2e9;
    for (int i = 1, j; i <= n; i ++)
      if (des[i] == i) {
        j = i;
        while (des[j] == j && j <= n) j ++;
        int res = 0;
        bool bad = 0;
        for (int k = 1; k <= n; k ++) {
          if (k < i) res += p[k].first + p[k].second;
          else if (k < j) res += mabs(p[k].first - p[k].second);
          else res += L + L - (p[k].first + p[k].second);
          if (k < i && des[k] >= i) bad = 1;
          if (k >= j && des[k] < j) bad = 1;
        }
        if (!bad) ans = min(ans, res);
        i = j - 1;
      }
    for (int i = 0; i <= n; i ++) {
      for (int j = 0; j <= n; j ++) {
        int res = 0;
        for (int k = 1; k <= n; k ++) {
          if ((des[k] <= j) != (k <= i))
            res += L + L - mabs(p[k].first - p[k].second);
          else if (k <= i) res += p[k].first + p[k].second;
          else res += L + L - (p[k].first + p[k].second);
        }
        ans = min(ans, res);
      }
    }
    return ans;
  }
};
