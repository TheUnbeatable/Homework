#include <bits/stdc++.h>
using namespace std;

class SwitchingGame {
private:
  int nxt[55][55];
public:
  inline int timeToWin(vector <string> states) {
    int n = states.size(), m = states[0].length();
    for (int i = n - 1; ~ i; i --) {
      for (int j = 0; j < m; j ++) {
        int d = ( states[i][j] == '?' ? -1 : (states[i][j] == '+') );
        if (i == n - 1) nxt[i][j] = d;
        else {
          if (~ d) nxt[i][j] = d;
          else nxt[i][j] = nxt[i + 1][j];
        }
      }
    }
    vector <int> cur(m);
    int ans = 0;
    for (int i = 0; i < n; i ++) {
      bool m0 = 0, m1 = 0;
      for (int j = 0; j < m; j ++) {
        int d = ( states[i][j] == '?' ? -1 : (states[i][j] == '+') );
        if (cur[j] == 0 && d == 1) m0 = 1;
        if (cur[j] == 1 && d == 0) m1 = 1;
      }
      ans += m0 + m1 + 1;
      if (m0) {
        for (int j = 0; j < m; j ++)
          if (cur[j] == 0 && nxt[i][j] == 1) cur[j] = 1;
      }
      if (m1) {
        for (int j = 0; j < m; j ++)
          if (cur[j] == 1 && nxt[i][j] == 0) cur[j] = 0;
      }
    }
    return ans;
  }
};
