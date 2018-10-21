#include <cstdio>
#include <iostream>
#define rs register short
using namespace std;

const int N = 2005;

inline bool blank(char ch) {
  return ch == ' ' || ch == '\n' || ch == '\r' || ch == '\t';
}

inline void Rchar(char &ch) {
  while (blank(ch = getchar()));
}

char ch[N][N];
short ri[N][N];
short sta[N], up[N], top = 0;

int main() {
  int n, m, empty = 0;
  scanf("%d%d", &n, &m);
  for (rs i = 1; i <= n; i ++)
    for (rs j = 1; j <= m; j ++) {
      Rchar(ch[i][j]);
      empty += (ch[i][j] == '.');
    }
  for (rs i = m; i; i --) ri[1][i] = m - i + 1;
  short inv, same;
  for (rs i = 2; i <= n; i ++) {
    inv = same = 0;
    for (rs j = m; j; j --) {
      if (ch[i][j] == ch[i - 1][j]) {same ++; inv = 0;}
      else {inv ++; same = 0;}
      ri[i][j] = max(same, inv);
    }
  }
  int ans = 0;
  for (rs j = 1; j <= m; j ++) {
    top = 0;
    for (rs i = 1; i <= n + 1; i ++) {
      rs d = i, t = ri[i][j];
      while (top > 0 && sta[top] >= t) {
	if (up[top] != 1) ans = max(ans, (int)(i - up[top] + 1) * sta[top]);
	else ans = max(ans, (int)(i - up[top]) * sta[top]);
	d = up[top --];
      }
      sta[++ top] = t;
      up[top] = d;
    }
  }
  printf("%d\n", ans);
  return 0;
}
