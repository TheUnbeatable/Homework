#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
#define travel(x, i) for (int i = fir[x]; i; i = e[i].nxt)
#define rep(i, x, y) for (int i = (x); i <= (y); i ++)
using namespace std;

typedef long long LL;
const int N = 2e5 + 5;

namespace Graph2 {
    struct edge {
	int nxt, to;
    } e[N << 1];
    int fir[N], cnt = 0, dep[N], fa[N][18];

    inline void addedge(int x, int y) {
	e[++ cnt] = (edge){fir[x], y};
	fir[x] = cnt;
    }
    inline void Dfs(int x, int f) {
	dep[x] = dep[f] + 1;
	fa[x][0] = f;
	rep(i, 1, 17)
	    fa[x][i] = fa[fa[x][i - 1]][i - 1];
	travel(x, i)
	    if (e[i].to != f) Dfs(e[i].to, x);
    }
    inline int LCA(int x, int y) {
	if (dep[x] < dep[y]) swap(x, y);
	for (int i = 17; (~ i) && dep[x] != dep[y]; i --)
	    if (dep[fa[x][i]] >= dep[y]) x = fa[x][i];
	if (x == y) return x;
	for (int i = 17; (~ i) && fa[x][0] != fa[y][0]; i --)
	    if (fa[x][i] != fa[y][i]) {
		x = fa[x][i];
		y = fa[y][i];
	    }
	return fa[x][0];
    }
    inline int Dis(int x, int y) {
	return dep[x] + dep[y] - (dep[LCA(x, y)] << 1);
    }
}

namespace Graph1 {
    struct edge {
	int nxt, to;
    } e[N << 1];
    int fir[N], cnt = 0, dep[N], MAX;
    bool safe[N], flag;

    inline void addedge(int x, int y) {
	e[++ cnt] = (edge){fir[x], y};
	fir[x] = cnt;
    }
    inline void Dfs(int x, int f) {
	if (flag) return;
	dep[x] = dep[f] + 1;
	if (Graph2 :: dep[x] <= dep[x]) return;
	MAX = max(MAX, max(dep[x], Graph2 :: dep[x]) << 1);
	if (safe[x]) {
	    flag = 1;
	    return;
	}
	travel(x, i)
	    if (e[i].to != f) Dfs(e[i].to, x);
    }
}

using namespace Graph1;

int main() {
    int n, x, y, u, v;
    scanf("%d%d%d", &n, &x, &y);
    dep[0] = -1;
    Graph2 :: dep[0] = -1;
    rep(i, 1, n - 1) {
	scanf("%d%d", &u, &v);
	addedge(u, v);
	addedge(v, u);
    }
    rep(i, 1, n - 1) {
	scanf("%d%d", &u, &v);
	Graph2 :: addedge(u, v);
	Graph2 :: addedge(v, u);
    }
    Graph2 :: Dfs(y, 0);
    rep(i, 1, n) {
	travel(i, j) {
	    if (Graph2 :: Dis(i, e[j].to) >= 3) safe[i] = 1;
	}
    }
    Dfs(x, 0);
    if (flag) puts("-1");
    else printf("%d\n", MAX);
    return 0;
}
