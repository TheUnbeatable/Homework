#include <cstdio>
#include <iostream>
#include <queue>
#include <ctime>
#include <cmath>
#include <cstring>
#include <algorithm>
using namespace std;

typedef long double LD;
const int N = 55;

namespace Geometry {
  typedef pair <LD, LD> range;
  const LD eps = 1e-10;
  const LD INF = 1e20;
  struct vec {
    LD x, y;
    vec() {};
    vec(LD _x, LD _y) : x(_x), y(_y) {}
    inline vec operator + (const vec &o) { return vec(x + o.x, y + o.y); }
    inline vec operator - (const vec &o) { return vec(x - o.x, y - o.y); }
    inline vec operator * (LD o) { return vec(x * o, y * o); }
    inline vec operator / (LD o) { return vec(x / o, y / o); }
    inline LD operator * (const vec &o) { return x * o.x + y * o.y; }
    inline LD operator ^ (const vec &o) { return x * o.y - y * o.x; }
    inline LD norm() { return x * x + y * y; }
    inline LD abs() { return sqrt(x * x + y * y); }
    inline vec unit() { return vec(x / abs(), y / abs()); }
    inline LD degree() { return atan2(y, x); }
    friend ostream &operator << (ostream &o, vec v) {
      o << "(" << v.x << "," << v.y << ")";
      return o;
    }
  };
  struct seg {
    vec p, d;
    seg() {}
    seg(vec s, vec t) : p(s), d(t - s) {}
  };
  struct cir {
    vec o;
    LD r;
    cir() {}
    cir(vec _o, LD _r) : o(_o), r(_r) {}
  };
  inline vec foot(vec V, seg S) {
    return S.p + S.d * ((S.d * (V - S.p)) / S.d.norm());
  }
  inline range inter(cir C, seg S) {
    vec f = foot(C.o, S);
    if (C.r * C.r - (C.o - f).norm() < eps) return make_pair(-1, -1);
    LD dis = sqrt(C.r * C.r - (C.o - f).norm()), q = (S.d * (C.o - S.p)) / S.d.abs();
    return make_pair(max((LD)0, q - dis), min(S.d.abs(), q + dis));
  }
}
using namespace Geometry;

namespace NetWork {
  const int V = 7000, E = 2e5;
  const int S = V - 2, T = V - 1;
  struct edge {
    int nxt, to; LD cap;
  } e[E];
  int fir[V], lst[V], cnt;
  int dis[V];
  inline void clr() {
    memset(fir, 0, sizeof fir); cnt = 1;
  }
  inline void addedge(int x, int y, LD c) {
    e[++ cnt] = (edge) { fir[x], y, c }; fir[x] = cnt;
    e[++ cnt] = (edge) { fir[y], x, 0 }; fir[y] = cnt;
  }
  inline int Bfs() {
    memset(dis, -1, sizeof dis);
    dis[S] = 0;
    queue <int> Q; Q.push(S);
    memcpy(lst, fir, sizeof fir);
    while (Q.size()) {
      int x = Q.front(); Q.pop();
      for (int i = fir[x]; i; i = e[i].nxt)
        if (e[i].cap > eps && dis[e[i].to] == -1) {
          Q.push(e[i].to);
          dis[e[i].to] = dis[x] + 1;
        }
    }
    return dis[T];
  }
  inline LD Dfs(int x, LD flow) {
    if (x == T || flow <= eps) return flow;
    LD res = 0;
    for (int &i = lst[x]; i; i = e[i].nxt)
      if (e[i].cap > eps && dis[x] + 1 == dis[e[i].to]) {
        LD d = Dfs(e[i].to, min(flow, e[i].cap));
        flow -= d; res += d;
        e[i].cap -= d; e[i ^ 1].cap += d;
        if (flow <= eps) return res;
      }
    if (res < eps) dis[x] = -1;
    return res;
  }
  inline LD Maxflow() {
    LD ans = 0, delta;
    while (~ Bfs()) {
      delta = Dfs(S, INF);
      ans += delta;
      if (delta < eps) break;
    }
    return ans;
  }
}
using namespace NetWork;

class BarbarianInvasion2 {
private :
  int n, m;
  vec fro[N], to[N];
  LD C;
public :
  inline bool check(LD dis) {
    int sz = 0, top = 0;
    NetWork :: clr();
    static LD tab[N << 1];
    for (int i = 1; i <= n; i ++) {
      range rec; top = 2;
      tab[1] = 0;
      tab[2] = (fro[i + 1] - fro[i]).abs();
      seg cur = seg(fro[i], fro[i + 1]);
      for (int j = 1; j <= m; j ++) {
        rec = inter(cir(to[j], dis), cur);
        if (rec.first == -1 || rec.first == rec.second) continue;
        tab[++ top] = rec.first;
        tab[++ top] = rec.second;
      }
      sort(tab + 1, tab + top + 1);
      top = unique(tab + 1, tab + top + 1) - tab - 1;
      for (int j = 1; j < top; j ++)
        addedge(S, sz + j, tab[j + 1] - tab[j]);
      for (int j = 1; j <= m; j ++) {
        rec = inter(cir(to[j], dis), cur);
        if (rec.first == -1 || rec.first == rec.second) continue;
        for (int k = 1; k < top && tab[k] < rec.second; k ++)
          if (rec.first <= tab[k]) addedge(sz + k, 6000 + j, INF);
      }
      sz += top;
    }
    for (int i = 1; i <= m; i ++)
      addedge(6000 + i, T, C / m);
    LD flow = Maxflow();
    return flow + eps >= C;
  }
  inline double minimumTime(vector <int> boundaryX, vector <int> boundaryY, vector <int> cityX, vector <int> cityY) {
    n = boundaryX.size(); m = cityX.size(); C = 0;
    for (int i = 0; i < n; i ++)
      fro[i + 1] = vec(boundaryX[i], boundaryY[i]);
    fro[n + 1] = fro[1];
    for (int i = 1; i <= n; i ++)
      C += (fro[i + 1] - fro[i]).abs();
    for (int i = 0; i < m; i ++)
      to[i + 1] = vec(cityX[i], cityY[i]);
    LD ans = 0, L = 0, R = 5000, mid;
    for (int i = 1; i <= 100 && R - L > eps; i ++) {
      mid = (R + L) / 2;
      if (check(mid)) R = mid - eps, ans = mid;
      else L = mid + eps;
    }
    return (double)ans;
  }
};
