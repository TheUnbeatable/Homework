#include <cstdio>
#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

const int N = 1e5 + 5;

struct query {
  int x, y, z, id;
} qry[N], tmp[N];

struct Ope {
  int Ql, Qr, El, Er, lay;
};
queue <Ope> Q;

int x[N], y[N], ans[N];
int n, m, q;

namespace Union_Set {
  int fa[N], size[N];
  inline int getf(int x) {
    return fa[x] == x ? x : fa[x] = getf(fa[x]);
  }
  inline void Init() {
    for (int i = 1; i <= n; i ++) fa[i] = i, size[i] = 1;
  }
  inline void Union(int x, int y) {
    x = getf(x); y = getf(y);
    if (x != y) fa[y] = x, size[x] += size[y];
  }
  inline int Query(int x, int y) {
    x = getf(x); y = getf(y);
    if (x != y) return size[x] + size[y];
    else return size[x];
  }
}
using namespace Union_Set;

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= m; i ++) scanf("%d%d", &x[i], &y[i]);
  scanf("%d", &q);
  for (int i = 1; i <= q; i ++) scanf("%d%d%d", &qry[i].x, &qry[i].y, &qry[i].z), qry[i].id = i;
  Q.push((Ope){1, q, 1, m, 1});
  int Ql, Qr, El, Er, lay = 0, Emid, Nl, Nr, st = 1;
  Ope cur;
  while (!Q.empty()) {
    cur = Q.front();
    Q.pop();
    if (cur.lay != lay) {lay ++; st = 1; Init();}
    El = cur.El; Er = cur.Er;
    Ql = cur.Ql; Qr = cur.Qr;
    //printf("%d %d %d %d %d\n", lay, El, Er, Ql, Qr);
    if (El == Er) {
      for (int i = Ql; i <= Qr; i ++) ans[qry[i].id] = El;
      continue;
    }
    Emid = (El + Er) >> 1;
    for (int i = st; i <= Emid; i ++) Union(x[i], y[i]);
    st = Emid;
    Nl = Ql; Nr = Qr;
    for (int i = Ql, v; i <= Qr; i ++) {
      v = Query(qry[i].x, qry[i].y);
      if (v < qry[i].z) tmp[Nr --] = qry[i];
      else tmp[Nl ++] = qry[i];
    }
    for (int i = Ql; i < Nl; i ++) qry[i] = tmp[i];
    for (int i = Qr; i > Nr; i --) qry[i] = tmp[i];
    Q.push((Ope){Ql, Nl - 1, El, Emid, lay + 1});
    Q.push((Ope){Nr + 1, Qr, Emid + 1, Er, lay + 1});
  }
  for (int i = 1; i <= q; i ++) printf("%d\n", ans[i]);
  return 0;
}
