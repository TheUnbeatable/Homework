#include <cstdio>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <map>
#define rs register short
#define ri register int
using namespace std;

typedef long long LL;
const int N = 1e5 + 5;

LL prime[N], sqr[N], cub[N];
int tot = 0;
bool notp[N];
map <LL, int> mp;
map <LL, LL> oppo;

inline void find_primes() {
  for (int i = 2; i < N; i ++) {
    if (!notp[i]) prime[++ tot] = i, sqr[tot] = prime[tot] * prime[tot], cub[tot] = sqr[tot] * prime[tot];
    for (int j = 1; j <= tot; j ++) {
      if (prime[j] * i >= N) break;
      notp[prime[j] * i] = 1;
      if (i % prime[j] == 0) break;
    }
  }
}

inline bool iscube(LL x) {
  LL t = pow(x, 1.0 / 3) + 0.5;
  return t * t * t == x;
}

inline bool issqr(LL x) {
  LL t = sqrt(x) + 0.5;
  return t * t == x;
}

int main() {
  find_primes();
  int n, ans = 0, p, cnt;
  LL x, Dec, Inc;
  scanf("%d", &n);
  for (ri i = 1; i <= n; i ++) {
    scanf("%lld", &x);
    if (iscube(x)) {ans = 1; continue;}
    Dec = Inc = 1;
    for (rs j = 1; cub[j] <= x; j ++)
      if (x % prime[j] == 0) {
	cnt = 0;
	while (x % prime[j] == 0) {
	  x /= prime[j];
	  cnt ++;
	}
	cnt %= 3;
	if (cnt == 0) continue;
	if (cnt == 1) Dec *= prime[j], Inc *= sqr[j];
	else Dec *= sqr[j], Inc *= prime[j];
      }
    if (issqr(x)) Inc *= (LL)(sqrt(x) + 0.5), Dec *= x;
    else Inc *= x * x, Dec *= x;
    mp[Dec] ++;
    oppo[Dec] = Inc;
  }
  LL o;
  map <LL, int> :: iterator tmp;
  for (map <LL, int> :: iterator it = mp.begin(); it != mp.end(); it ++) {
    o = oppo[it -> first];
    tmp = mp.find(o);
    if (tmp != mp.end()) {
      ans += max(it -> second, tmp -> second);
      mp.erase(tmp);
    }
    else ans += it -> second;
  }
  printf("%d\n", ans);
  return 0;
}
