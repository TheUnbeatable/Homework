#include <cstdio>
#include <iostream>
#include <cmath>
using namespace std;

const int N = 5e5 + 5;

template <typename T> inline void Read(T &x) {
  x = 0; char ch;
  while (!isdigit(ch = getchar()));
  do {x = (x << 1) + (x << 3) + ch - '0';} while (isdigit(ch = getchar()));
}

int arr[N], pos[N], cant[N];

int main() {
  int n, d, q, x;
  Read(n); Read(d);
  for (int i = 1; i <= n; i ++) {
    Read(arr[i]);
    if (pos[i - 1] <= d) {
      if (abs(pos[i - 1] + arr[i] - d) < abs(pos[i - 1] - d))
	pos[i] = pos[i - 1] + arr[i];
      else pos[i] = pos[i - 1];
    }
    else {
      if (abs(pos[i - 1] - arr[i] - d) < abs(pos[i - 1] - d))
	pos[i] = pos[i - 1] - arr[i];
      else pos[i] = pos[i - 1];
    }
  }
  cant[n + 1] = 1;
  for (int i = n; i >= 1; i --) {
    if (arr[i] >= cant[i + 1] * 2) cant[i] = cant[i + 1];
    else cant[i] = cant[i + 1] + arr[i];
  }
  Read(q);
  while (q --) {
    Read(x);
    if (abs(pos[x - 1] - d) >= cant[x + 1]) puts("YES");
    else puts("NO");
  }
  return 0;
}
