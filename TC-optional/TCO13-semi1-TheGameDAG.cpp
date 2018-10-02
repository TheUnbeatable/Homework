#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;

class TheGameDAG {
private:
  int id[11], n, A, B;
  double x, xy;
  
  inline void calc() {
    double ps = 1, pps = 1;
    for (int i = 1; i <= n; i ++) {
      int tot = 0;
      for (int j = i; j <= n; j ++)
        if (id[j] < i) tot ++;
      ps /= tot;
      pps /= tot;
      ps *= 1 << max(0, id[i] - 1);
      if (i != B) {
        pps *= 1 << max(0, id[i] - 1);
      } else {
        if (id[B] < A) pps = 0;
        else if (i == B)
          pps *= 1 << max(0, id[i] - 1 - (id[B] != A));
      }
    }
    x += ps; xy += pps;
  }
  inline void Dfs(int x) {
    if (x > n) return calc();
    for (int i = 0; i < x; i ++) {
      id[x] = i; Dfs(x + 1);
    }
  }
public:
  inline double getProbability(vector <int> P, int a, int b) {
    n = P.size();
    for (int i = 0; i < n; i ++) {
      if (P[i] == a) A = i + 1;
      if (P[i] == b) B = i + 1;
    }
    if (A > B) return 0;
    x = xy = 0; Dfs(1);
    return xy / x;
  }
};
