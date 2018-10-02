#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

class RabbitsAndCakes {
public:
  inline long long getNumber(int minR, int maxR, int minC, int maxC) {
    long long res = 0;
    // rabbit less than / equal to cakes (c / r >= 1)
    for (int i = minR; i <= maxR; i ++)
      res += max(0, maxC - max(i, minC) + 1); 
    // rabbit more than cakes (c / r < 1)
    for (int i = 1; i <= maxC; i ++)
      for (int j = i, k = i + 1; j <= maxC && k <= maxR; j += i, k += i + 1)
        if (j >= minC && k >= minR) res ++;
    return res;
  }
};
