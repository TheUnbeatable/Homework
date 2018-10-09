#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

const int N = 1e5 + 50;

struct edge {
  int nxt, to;
} e[N << 1];
int fir[N], cnt = 1;

inline void addedge(int x, int y) {
  e[++ cnt] = (edge) { fir[x], y }; fir[x] = cnt;
}

class GameWithTree {
private:
  string col;
  inline pair <int, int> Dfs(int x) {
    int dep = 0, nim = 0;
    for (int i = fir[x]; i; i = e[i].nxt) {
      pair <int, int> tmp = Dfs(e[i].to);
      dep = max(dep, tmp.first + 1);
      nim ^= tmp.second;
    }
    if (col[x] == 'W')
      nim += 1 << dep;
    return make_pair(dep, nim);
  }
public:
  inline string winner(vector <int> parent, string color) {
    col = color;
    int n = parent.size();
    for (int i = 0; i < n; i ++)
      addedge(parent[i], i + 1);
    if (Dfs(0).second) return "Masha";
    else return "Petya";
  }
};
