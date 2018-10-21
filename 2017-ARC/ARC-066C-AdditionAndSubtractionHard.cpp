#include <cstdio>
#include <iostream>
#define Max 1
#define Min -1
using namespace std;

typedef long long LL;
const int N = 1e5 + 5;

int arr[N], ope[N], n;
LL dp[3][N];
char s[5];

int main() {
  scanf("%d", &n);
  ope[1] = 1;
  for (int i = 1; i <= n; i ++) {
    scanf("%d", &arr[i]);
    if (i != n) {
      scanf("%s", s);
      if (s[0] == '+') ope[i + 1] = 1;
      else ope[i + 1] = -1;
    }
  }
  dp[1][0] = dp[2][0] = -1e16;
  for (int i = 1; i <= n; i ++) {
    dp[0][i] = dp[0][i - 1] + arr[i] * ope[i];
    dp[1][i] = dp[1][i - 1] - arr[i] * ope[i];
    dp[2][i] = dp[2][i - 1] + arr[i] * ope[i];
    if (ope[i] == -1) {
      dp[2][i] = max(dp[2][i], dp[1][i]);
      dp[1][i] = max(dp[1][i], dp[0][i]);
    }
    dp[0][i] = max(dp[0][i], dp[1][i]);
    dp[1][i] = max(dp[1][i], dp[2][i]);
  }
  printf("%lld\n", dp[0][n]);
  return 0;
}
