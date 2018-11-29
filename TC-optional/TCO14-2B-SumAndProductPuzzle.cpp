#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
const int N = 5e6 + 50;

bitset <N> notp, fail;
int pri[N / 4], m;

inline void Init() {
  for (int i = 2; i < N; i ++) {
    if (!notp[i]) pri[++ m] = i;
    for (int j = 1; j <= m; j ++) {
      int t = pri[j] * i;
      if (t >= N) break;
      notp[t] = 1;
      if (i % pri[j] == 0) break;
    }
  }
}

struct SumAndProductPuzzle {
public:
  inline LL getSum(int A, int B) {
    Init();
    for (int i = 2; i <= B; i ++)
      for (int j = i + i, k = 2; j <= B; j += i, k ++)
        if (notp[i + k - 1]) fail[j + 1] = 1;
    LL ans = 0;
    for (int i = A; i <= B; i ++)
      if (!fail[i] && notp[i - 1]) ans += i;
    return ans;
  }
};
