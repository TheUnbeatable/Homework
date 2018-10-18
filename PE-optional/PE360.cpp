#include <cstdio>
#include <iostream>
#include <set>
#include <vector>
using namespace std;

typedef long long LL;

int n = 9765625;
vector <pair <int, int> > buc[10000000];
set <pair <pair <int, int>, int> > rec;

template <typename T>
inline T mabs(T x) {
  return max(x, - x);
}

inline void Add(int N, int M, int P, int Q) {
  int a = mabs(N * N + M * M - P * P - Q * Q);
  int b = mabs(2 * (M * Q + N * P));
  int c = mabs(2 * (N * Q - M * P));
  if (a > b) swap(a, b);
  if (b > c) swap(b, c);
  if (a > b) swap(a, b);
  while (1ll * a * a + 1ll * b * b + 1ll * c * c != 1ll * n * n) {
    a *= 5; b *= 5; c *= 5;
  }
  rec.insert(make_pair(make_pair(a, b), c));
}

int main() {
  for (int i = 0; i * i <= n; i ++)
    for (int j = i; j * j + i * i <= n; j ++)
      buc[i * i + j * j].push_back(make_pair(i, j));
  int N, M, P, Q;
  for (int i = n; i; i /= 5)
    for (int j = 0; j <= i; j ++) {
      for (auto a : buc[j])
        for (auto b : buc[i - j]) {
          N = a.first; M = a.second;
          P = b.first; Q = b.second;
          Add(N, M, P, Q);
          Add(M, N, P, Q);
        }
    }
  long long ans = 0;
  for (auto i : rec) {
    int a = i.first.first;
    int b = i.first.second;
    int c = i.second;
    if (a == 0 && b == 0) ans += c * 6ll;
    else if (a == 0) {
      if (b == c) ans += (a + b + c) * 12ll;
      else ans += (a + b + c) * 24ll;
    }
    else if (a == b && b == c) ans += a * 24ll;
    else if (a == b || b == c) ans += (a + b + c) * 24ll;
    else ans += (a + b + c) * 48ll;
  }
  printf("%lld\n", ans * 1024);
  return 0;
}
