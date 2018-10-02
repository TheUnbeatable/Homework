#include <cstdio>
#include <iostream>
#include <stack>
using namespace std;

typedef pair <int, int> pii;
typedef long long LL;
const int N = 5007;
const int M = 202;

LL G[N][N], D[N];
int b[M][N], l[N], n, m;
stack <pii> st;

inline void add(int l, int m, int r, int val) {
  G[l][m] += val;
  G[l][r + 1] -= val;
  G[m + 1][m] -= val;
  G[m + 1][r + 1] += val;
}

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 2; i <= n; i ++) {
    scanf("%lld", &D[i]);
    D[i] += D[i - 1];
  }
  for (int i = 1; i <= n; i ++)
    for (int j = 1; j <= m; j ++) scanf("%d", &b[j][i]);
  for (int j = 1; j <= m; j ++) {
    while (!st.empty()) st.pop();
    st.push(make_pair(0, 2e9));
    for (int i = 1; i <= n; i ++) {
      while (st.top().second < b[j][i]) st.pop();
      l[i] = st.top().first + 1;
      st.push(make_pair(i, b[j][i]));
    }
    while (!st.empty()) st.pop();
    st.push(make_pair(n + 1, 2e9));
    for (int i = n; i >= 1; i --) {
      while (st.top().second <= b[j][i]) st.pop();
      add(l[i], i, st.top().first - 1, b[j][i]);
      st.push(make_pair(i, b[j][i]));
    }
  }
  LL ans = 0;
  for (int i = 1; i <= n; i ++)
    for (int j = 1; j <= n; j ++) {
      G[i][j] += G[i - 1][j] + G[i][j - 1] - G[i - 1][j - 1];
      if (i <= j) ans = max(ans, D[i] - D[j] + G[i][j]);
    }
  printf("%lld\n", ans);
  return 0;
}
