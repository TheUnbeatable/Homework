#include <cstdio>
#include <iostream>
#include <queue>
#define X first
#define Y second
#define mp make_pair
using namespace std;

typedef long long LL;
typedef pair <double, double> Point;
const int N = 5e5 + 50;

Point Q[N];
int n, L, he = 1, ta = 0;

template <typename T> inline void Read(T &x) {
  x = 0; char ch = 0;
  while (!isdigit(ch = getchar()));
  do {x = (x << 1) + (x << 3) + ch - '0';} while (isdigit(ch = getchar()));
}

inline void Desert(double right) {
  while (he < ta && Q[he + 1].X >= right) he ++;
  if (Q[he].X > right) {
    Q[he].Y = Q[he + 1].Y + (Q[he].Y - Q[he + 1].Y) / (Q[he].X - Q[he + 1].X) * (right - Q[he + 1].X);
    Q[he].X = right;
  }
}

inline void Insert(Point P) {
  while (he < ta && (Q[ta].X - P.X) * (Q[ta - 1].Y - P.Y) >= (Q[ta - 1].X - P.X) * (Q[ta].Y - P.Y)) ta --;
  Q[++ ta] = P;
}

int main() {
  Read(n); Read(L);
  Q[++ ta] = mp(0, 0);
  LL x, y;
  for (int i = 1; i <= n; i ++) {
    Read(y); Read(x);
    y *= x;
    if (i != 1) Desert(Q[he].first - x);
    Insert(mp(Q[ta].X - x, Q[ta].Y - y));
    printf("%.7lf\n", (Q[he].second - Q[ta].second) / L);
  }
  return 0;
}
