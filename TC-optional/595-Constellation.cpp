#include <cstdio>
#include <iostream>
#include <vector>
using namespace std;

typedef long double ld;

class Constellation {
private:
  struct vec {
    ld x, y;
    vec() {}
    vec(ld _x, ld _y) : x(_x), y(_y) {}
    inline vec operator - (const vec &o) const {
      return vec( x - o.x, y - o.y );
    }
    inline ld operator ^ (const vec &o) const {
      return x * o.y - y * o.x;
    }
  } p[60];
  int n;
public:
  inline double expectation(vector <int> x, vector <int> y, vector <int> prob) {
    srand(20011227);
    n = x.size();
    for (int i = 1; i <= n; i ++)
      p[i] = vec( x[i - 1] + rand() % 20 * 1e-10,
                  y[i - 1] + rand() % 20 * 1e-10 );
    ld ans = 0;
    for (int i = 1; i <= n; i ++)
      for (int j = i + 1; j <= n; j ++) {
        ld cl = 1, cr = 1;
        vec t = p[j] - p[i];
        for (int k = 1; k <= n; k ++)
          if (k != i && k != j) {
            if ((t ^ (p[k] - p[i])) > 0)
              cl *= 1 - prob[k - 1] * 1e-3;
            else
              cr *= 1 - prob[k - 1] * 1e-3;
          }
        ans += (p[i] ^ p[j]) * (cr - cl) * prob[i - 1] * 1e-3 * prob[j - 1] * 1e-3;
      }
    return ans * 0.5;
  }
};
