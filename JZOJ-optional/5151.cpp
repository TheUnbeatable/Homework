#include <bits/stdc++.h>
using namespace std;

const int N = 1030;
const int mod = 1e9 + 7;

int f[2][N][N], n;

inline void Inc(int &x, int y) { (x += y) >= mod ? (x -= mod) : 0; }

inline void Sub(int &x, int y) { (x -= y) < 0 ? (x += mod) : 0; }

int main() {
  freopen("never.in", "r", stdin);
  freopen("never.out", "w", stdout);
  scanf("%d", &n);
  int cur = 0, nxt = 1;
  f[cur][1023][1023] = 1;
  for (int i = 1, a; i <= n; i ++) {
    scanf("%d", &a);
    for (int j = 0; j < 1024; j ++) {
      for (int k = j; k; k = (k - 1) & j) f[nxt][j][k] = f[cur][j][k];
      f[nxt][j][0] = f[cur][j][0];
    }
    for (int j = 0; j < 1024; j ++)
      for (int k = j; ; k = (k - 1) & j) {
        if (f[cur][j][k]) {
          Inc(f[nxt][j & a][k & a], f[cur][j][k]);
          Sub(f[nxt][(j & a) | k][k & a], f[cur][j][k]);
        }
        if (!k) break;
      }
    swap(cur, nxt);
  }
  printf("%d\n", f[cur][0][0]);
  return 0;
}
