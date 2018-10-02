#include <cstdio>
#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;

typedef long long LL;
typedef vector <int> vi;

struct P {
  int x, y;
  P() { x = y = 0; }
  P(int _x, int _y): x(_x), y(_y) {}
  inline P operator - (const P &o) const {
    return P(x - o.x, y - o.y);
  }
  inline long long operator ^ (const P &o) const {
    return 1ll * x * o.y - 1ll * y * o.x;
  }
};

class ToastJumping {
private:
  P sta[60000];
  inline void simplify(LL &x, LL &y) {
    LL d = __gcd(x, y);
    x /= d; y /= d;
  }
  inline int solve(int x, int y, int d) {
    if (x < 0) x = - x;
    if (y < 0) y = - y;
    if (!x && !y) return 0;
    if (!x || !y) {
      int k = sqrt(d) + 0.5;
      if (k * k > d) k --;
      return (x + y - 1) / k + 1;
    }
    int j = sqrt(d) + 1;
    while (j * j > d) j --;
    int top = 0;
    for (int i = 0; i * i <= d; i ++) {
      while (i * i + j * j > d) j --;
      while (top >= 2 && ( (sta[top] - sta[top - 1]) ^ (P(i, j) - sta[top - 1]) ) >= 0) top --;
      sta[++ top] = P(i, j);
      if ((i + 1) * (i + 1) > d && j) {
        j = 0; i --;
      }
    }
    for (int i = 2; i <= top; i ++)
      if (1ll * y * sta[i].x >= 1ll * x * sta[i].y) {
        LL h1 = 1ll * sta[i - 1].y * x - 1ll * y * sta[i - 1].x;
        LL h2 = 1ll * y * sta[i].x - 1ll * sta[i].y * x;
        LL up = sta[i - 1].x * (h1 + h2) + (sta[i].x - sta[i - 1].x) * h1;
        LL down = h1 + h2;
        simplify(up, down);
        swap(up, down);
        if (x % down == 0) return up * (x / down);
        return (int)(1.0 * up * x / down) + 1;
      }
    throw;
  }
public:
  inline vi minJumps(vi x, vi y, vi d) {
    vi ans;
    for (size_t i = 0; i < x.size(); i ++)
      ans.push_back( solve(x[i], y[i], d[i]) );
    return ans;
  }
};
