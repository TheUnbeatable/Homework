#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

class WellTimedSearch {
public:
  inline double getProbability(int N, int A, int B) {
    int rb = N;
    long long Max = 0;
    if (A <= 23) rb = min(rb, 1 << (A - 1));
    for (int i = 1; i <= rb; i ++) {
      long long sum = 0, used = 0;
      if (B - A <= 23) sum = (1ll << (B - A + 1)) * i - i;
      else sum = N;
      used = A - 1;
      for (int j = (i + 1) >> 1; j > 1; j = (j + 1) >> 1) used += j - 1;
      sum = min(sum, N - used);
      Max = max(Max, sum);
    }
    return 1.0 * Max / N;
  }
};
