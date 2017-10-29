#include <cstdio>
#include <iostream>
using namespace std;

const int M = 105;

int n, m, arr[M];

int main() {
  int p1 = 0, p2 = 0;
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= m; i ++) {
    scanf("%d", &arr[i]);
    if (arr[i] & 1) {
      if (p1 && p2) return puts("Impossible"), 0;
      else if (!p1) p1 = i;
      else p2 = i;
    }
  }
  if (n == 1) return printf("1\n1\n1\n"), 0;
  if (m == 1) return printf("%d\n2\n%d 1\n", n, n - 1), 0;
  if (p2) {
    swap(arr[p1], arr[1]);
    swap(arr[p2], arr[m]);
  }
  else if (p1) swap(arr[p1], arr[1]);
  for (int i = 1; i <= m; i ++) printf("%d%c", arr[i], i == m ? '\n' : ' ');
  arr[1] ++; arr[m] --;
  if (arr[m] == 0) m --;
  printf("%d\n", m);
  for (int i = 1; i <= m; i ++) printf("%d%c", arr[i], i == m ? '\n' : ' ');
  return 0;
}
