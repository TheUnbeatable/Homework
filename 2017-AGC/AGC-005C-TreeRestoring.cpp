#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
#define fail return puts("Impossible"), 0
#define rep(i, x, y) for (int i = (x); i <= (y); i ++)
using namespace std;

const int N = 105;

int a[N];

int main() {
  int n, x;
  scanf("%d", &n);
  rep(i, 1, n) {
    scanf("%d", &x);
    a[x] ++;
  }
  int d = n - 1;
  while (!a[d]) d --;
  for (int i = 0; i <= d; i ++) {
    if (!a[max(i, d - i)]) fail;
    a[max(i, d - i)] --;
  }
  d = (d + 1) >> 1;
  rep(i, 1, d)
    if (a[i]) fail;
  puts("Possible");
  return 0;
}
