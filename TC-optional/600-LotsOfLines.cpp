#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

typedef long long longint;
const int N = 1210;

class LotsOfLines {
private:
  int a[N][N];
public:
  inline longint countDivisions(int A, int B) {
    longint ans = 0;
    for (int i = 0; i < A; i ++)
      for (int j = 0; j < B; j ++) {
        int &p = a[i][j] = (__gcd(i, j) == 1);
        if (!i || !j) p = 0;
        if (i) p += a[i - 1][j];
        if (j) p += a[i][j - 1];
        if (i && j) p -= a[i - 1][j - 1];
      }
    for (int i = 0; i < A; i ++)
      for (int j = 0; j < B; j ++) ans += a[i][j];
    return ans * 2 + A * B + (A - 1) * B + 1;
  }
};
