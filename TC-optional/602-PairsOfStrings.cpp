#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
const int mod = 1e9 + 7;

class PairsOfStrings {
private:
  inline LL Pow(LL x, LL e) {
    LL res = 1;
    for (; e; e >>= 1, x = x * x % mod)
      if (e & 1) res = res * x % mod;
    return res;
  }
public:
  int getNumber(int n, int k) {
    vector <int> d, f;
    for (int i = 1; i * i <= n; i ++)
      if (n % i == 0) {
        d.push_back(i);
        if (i * i != n) d.push_back(n / i);
      }
    sort(d.begin(), d.end());
    f.resize(d.size());
    LL ans = 0;
    for (size_t i = 0; i < d.size(); i ++) {
      long long tmp = Pow(k, d[i]);
      for (size_t j = 0; j < i; j ++)
        if (d[i] % d[j] == 0) tmp -= f[j];
      f[i] = tmp = (tmp % mod + mod) % mod;
      ans = (ans + tmp * d[i]) % mod;
    }
    return ans;
  }
};
