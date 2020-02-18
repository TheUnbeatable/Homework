#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long LL;
const int N = 1e6 + 50;
const LL M = 1e18;

bitset <N> notp;
int p[N / 10], m;

namespace fastIO {
#define buf_size 1500000
  bool EndofFile = 0;
  inline char gc() {
    static char buf[buf_size + 1], *l = buf, *r = buf;
    if (l == r) {
      l = buf;
      r = buf + fread(buf, 1, buf_size, stdin);
      if (l == r) { EndofFile = 1; return -1; }
    }
    return *l ++;
  }
  inline bool blank(char ch) {
    return ch == '\n' || ch == '\t' || ch == ' ' || ch == '\r' || EndofFile;
  }
  template <typename T>
  inline void read(T &x) {
    char ch; x = 0; int f = 1;
    while ( !isdigit(ch = gc()) && ch != '-' && !EndofFile );
    if (EndofFile) return;
    if (ch == '-') { f = -1; ch = gc(); }
    do { x = (x << 1) + (x << 3) + ch - '0'; }
    while (isdigit(ch = gc()) && !EndofFile);
    x *= f;
  }
  inline void read(double &x) {
    char ch; x = 0; int f = 1;
    while ( !isdigit(ch = gc()) && ch != '-' && !EndofFile );
    if (EndofFile) return;
    if (ch == '-') { f = -1; ch = gc(); }
    do { x = x * 10 + ch - '0'; }
    while ( isdigit( ch = gc() ) && !EndofFile );
    if (!EndofFile && ch == '.') {
      double base = 1;
      while ( isdigit(ch = gc()) && !EndofFile ) {
        base *= 0.1; x += base * (ch - '0');
      }
    }
    x *= f;
  }
  inline void read(char *s) {
    char ch = 0; while (blank(ch = gc()) && !EndofFile);
    while (!EndofFile && !blank(ch)) { *s = ch; s ++; ch = gc(); }
  }
  inline void read(char *s, char endchar) {
    char ch = 0; while (blank(ch = gc()) && !EndofFile);
    while (!EndofFile && ch != endchar) { *s = ch; s ++; ch = gc(); }
  }
  template <typename T>
  inline void write(T x) {
    static int buf[55]; int len = 0;
    if (!x) { putchar('0'); return; }
    if (x < 0) { x = - x; putchar('-'); }
    for (; x; x /= 10) buf[++ len] = x % 10;
    for (; len; len --) putchar(buf[len] + '0');
  }
  template <typename T>
  inline void writeln(T x) {
    write(x); putchar('\n');
  }
#undef buf_size
}
using namespace fastIO;


inline void init() {
  m = 0;
  for (int i = 2; i < N; i ++) {
    if (!notp[i]) p[++ m] = i;
    for (int j = 1; j <= m; j ++) {
      if (i * p[j] >= N) break;
      notp[i * p[j]] = 1;
      if (i % p[j] == 0) break;
    }
  }
}

map <LL, LL> rec;
LL tab[N], val[N];
__int128 ans = M;

int main() {
  init();
  rec[M] = 1;
  for (int i = m, top; i; i --) {
    top = 0;
    LL base = 1LL * p[i] * p[i] * p[i];
    for (map <LL, LL> :: reverse_iterator it = rec.rbegin();
         it != rec.rend(); it ++) {
      if (it -> first < base) break;
      tab[++ top] = it -> first;
      val[top] = it -> second;
    }
    LL tmp;
    for (int j = 1; j <= top; j ++) {
      tmp = tab[j] / base;
      while (tmp) {
        ans += val[j] * tmp;
        rec[tmp] += val[j];
        tmp /= p[i];
      }
    }
  }
  writeln(ans);
  return 0;
}
