#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#define Do(x, y) ((x) / (y))
#define Up(x, y) (((x) - 1) / (y) + 1)
using namespace std;

typedef long long LL;
const int N = 1e5 + 5e4;

class SetMultiples {
private :
  int tab[N + 10];
public :
  inline LL smallestSubset(LL A, LL B, LL C, LL D) {
    if (C * 2 <= D) return D - Do(D, 2);
    LL S = max(A, Do(B, 2) + 1), tmp, L, R, Rb = -1;
    LL ans = D - C + 1 + B - S + 1;
    memset(tab, 0, sizeof tab);
    for (LL i = S; i <= N && i <= B; i ++) {
      if (C % i == 0) tab[i] ++, tab[i + 1] --;
      else {
        tmp = C / i + 1;
        if (tmp * i <= D) tab[i] ++, tab[i + 1] --;
      }
    }
    for (LL i = N; i >= 1; i --) {
      L = Up(C, i);
      R = Do(D, i);
      L = max(L, S);
      R = min(R, B);
      if (L > R) continue;
      if (L <= N) {
        tab[L] ++;
        tab[min(R, (LL)N) + 1] --;
        L = N + 1;
        if (L > R) continue;
      }
      if (L > Rb) ans -= R - L + 1;
      else ans -= R - Rb;
      Rb = R;
    }
    for (LL i = S; i <= N && i <= B; i ++) {
      tab[i] += tab[i - 1];
      if (tab[i] > 0) ans --;
    }
    return ans;
  }
};
