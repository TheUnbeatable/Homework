#include <bits/stdc++.h>
using namespace std;

const int N = 2003;

bitset <N * N> bag;
int n;

int main() {
  bag[0] = 1;
  scanf("%d", &n);
  int sum = 0;
  for (int i = 1, a; i <= n; i ++) {
    scanf("%d", &a);
    sum += a;
    bag |= bag << a;
  }
  for (int i = (sum + 1) / 2; ; i ++)
    if (bag[i]) {
      printf("%d\n", i); return 0;
    }
  return 0;
}
