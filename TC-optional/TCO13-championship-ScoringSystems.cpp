#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

const int B = 50 * 1e4 + 50;
const int N = B * 2;

int up[N], low[N], n, sup[N], slow[N];

inline void chkmax(int &x, int y) { if (x < y) x = y; }
inline void chkmin(int &x, int y) { if (x > y) x = y; }

inline void update(int fro, int delta, int to) {
  if (up[to] > 1e9) {
    up[to] = sup[fro] + delta;
    low[to] = slow[fro] + delta;
    return;
  }
  chkmax(up[to], sup[fro] + delta);
  chkmin(low[to], slow[fro] + delta);
}

struct ScoringSystems {
public:
  inline string isEquivalent(vector <int> c, vector <int> s) {
    memset(up, 0x3f, sizeof up);
    memset(low, 0x3f, sizeof low);
    up[B] = low[B] = 0;
    n = c.size();
    int tot = 0;
    for (int i = 0; i < n; i ++) {
      for (int j = B - tot; j <= B + tot; j ++) {
        slow[j] = low[j]; sup[j] = up[j];
      }
      for (int j = B - tot; j <= B + tot; j ++) {
        if (slow[j] > 1e9) continue;
        update(j, s[i], j + c[i]);
        update(j, - s[i], j - c[i]);
      }
      tot += c[i];
    }
    for (int i = B - tot; i < B; i ++)
      if (up[i] < 1e9 && up[i] >= 0) return "Not Equivalent";
    if (up[B] != 0 || low[B] != 0)
      return "Not Equivalent";
    for (int i = B + 1; i <= B + tot; i ++)
      if (low[i] < 1e9 && low[i] <= 0) return "Not Equivalent";
    return "Equivalent";
  }
};
