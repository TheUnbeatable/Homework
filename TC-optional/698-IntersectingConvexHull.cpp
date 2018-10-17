#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;

typedef long long longint;
const int N = 111;
const longint mod = 1e9 + 7;

struct P {
  int x, y;
  P() {}
  P(int _x, int _y) : x(_x), y(_y) {}
  inline P operator + (const P o) const {
    return P(x + o.x, y + o.y);
  }
  inline P operator - (const P o) const {
    return P(x - o.x, y - o.y);
  }
  inline longint operator ^ (const P o) const {
    return 1ll * x * o.y - 1ll * y * o.x;
  }
};

class IntersectingConvexHull {
private:
  P p[N], l[N], r[N];
  int n, pw[N], C[N][N];
  inline void Init() {
    for (int i = 0; i < N; i ++) {
      C[i][0] = 1;
      for (int j = 1; j <= i; j ++)
        C[i][j] = ( C[i - 1][j - 1] + C[i - 1][j] ) % mod;
    }
  }
public:
  inline int count(vector <int> x, vector <int> y) {
    Init();
    n = x.size();
    for (int i = pw[0] = 1; i <= n; i ++)
      pw[i] = (pw[i - 1] << 1) % mod;
    for (int i = 0; i < n; i ++)
      p[i + 1] = P(x[i], y[i]);
    longint ans = 0, sub = 0;
    for (int i = 3; i <= n; i ++)
      for (int j = 3; i + j <= n; j ++)
        (ans += 1ll * C[n][i] * C[n - i][j]) %= mod;
    for (int i = 1; i <= n; i ++)
      for (int j = i + 1; j <= n; j ++) {
        int cntl = 0, cntr = 0;
        P a = p[i], b = p[j];
        for (int k = 1; k <= n; k ++)
          if (k != i && k != j) {
            if ( ((a - b) ^ (p[k] - b)) > 0 ) ++ cntl;
            else ++ cntr;
          }
        (sub += 1ll * (pw[cntl] - 1 - cntl) * (pw[cntr] - 1 - cntr)) %= mod;
      }
    ans = (ans + (mod - sub) * 2) % mod;
    return ans;
  }
};
