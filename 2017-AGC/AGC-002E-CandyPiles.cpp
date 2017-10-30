#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;

const int N = 1e5 + 5;

int a[N], n;

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i ++) scanf("%d", &a[i]);
  sort(a + 1, a + n + 1, greater <int> ());
  int i, j;
  for (i = 1; i < n && a[i + 1] >= i + 1; i ++);
  if ((a[i] - i) & 1) return !puts("First");
  if (a[i + 1] == i) {
    for (j = i + 1; j < n && a[j + 1] == i; j ++);
    if ((j - i) & 1) return !puts("First");
  }
  puts("Second");
  return 0;
}
