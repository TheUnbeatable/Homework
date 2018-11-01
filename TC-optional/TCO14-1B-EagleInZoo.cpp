#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;

class EagleInZoo {
private:
  int deg[55];
  vector <int> to[55];
  double f[55][105], C[105][105], pw[105], opw[105];
public:
  inline double calc(vector <int> parent, int K) {
    int n = parent.size() + 1;
    memset(f, 0, sizeof f);
    memset(deg, 0, sizeof deg);
    parent.insert(parent.begin(), 54);
    for (int i = 0; i <= K; i ++) {
      C[i][0] = 1;
      for (int j = 1; j <= i; j ++)
        C[i][j] = C[i - 1][j - 1] + C[i - 1][j];
    }
    for (int i = n - 1; ~ i; i --) {
      to[parent[i]].push_back(i);
      f[i][1] = 1;
      if (!to[i].size()) continue;
      double p = 1.0 / to[i].size();
      pw[0] = opw[0] = 1;
      for (int j = 1; j <= K; j ++) {
        pw[j] = pw[j - 1] * p;
        opw[j] = opw[j - 1] * (1 - p);
      }
      for (size_t j = 0; j < to[i].size(); j ++) {
        int x = to[i][j];
        for (int k = 2; k <= K; k ++)
          for (int l = 1; l < k; l ++)
            f[i][k] += f[x][l] * C[k - 2][l - 1] * pw[l] * opw[k - 1 - l];
      }
    }
    return f[0][K];
  }
};
