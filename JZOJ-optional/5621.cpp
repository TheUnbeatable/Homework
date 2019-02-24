#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 50;

int n;
double F[N], G[N], P[N];
vector <double> suf[N];
vector <pair <int, double> > E[N];

// F[x]: consider subtree x, F[x] denotes the probability that F[x] is **not** affected
// G[x]: not considering subtree x, G[x] denotes  the probability that x is **not** affected by its parent
// F[x] * G[x] equals the probability that x is **not** affected in the whole procedure

inline void calcf(int x, int f) {
  vector <double> &s = suf[x];
  vector <pair <int, double> > &e = E[x];
  for (vector <pair <int, double> > :: iterator it = e.begin(); it != e.end(); it ++)
    if (it -> first == f) {
      e.erase(it); break;
    }
  s.resize(e.size() + 1);
  s[e.size()] = 1 - P[x];
  for (int i = (int)e.size() - 1; i >= 0; i --) {
    calcf(e[i].first, x);
    s[i] = s[i + 1] * ( 1 - e[i].second * (1 - F[e[i].first]) );
  }
  F[x] = s[0];
}

inline void calcg(int x) {
  vector <double> &s = suf[x];
  vector <pair <int, double> > &e = E[x];
  double prefix = G[x];
  for (int i = 0; i < (int) e.size(); i ++) {
    G[e[i].first] = 1 - e[i].second * (1 - prefix * s[i + 1]);
    calcg(e[i].first);
    prefix *= ( 1 - e[i].second * (1 - F[e[i].first]) );
  }
}

int main() {
  freopen("attack.in", "r", stdin);
  freopen("attack.out", "w", stdout);
  scanf("%*d%d", &n);
  for (int i = 1, x, y, l; i < n; i ++) {
    scanf("%d%d%d", &x, &y, &l);
    E[x].push_back(make_pair(y, l * 0.01));
    E[y].push_back(make_pair(x, l * 0.01));
  }
  for (int i = 1, p; i <= n; i ++) {
    scanf("%d", &p); P[i] = p * 0.01;
  }
  calcf(1, 0);
  G[1] = 1;
  calcg(1);
  double ans = 0;
  for (int i = 1; i <= n; i ++) ans += F[i] * G[i];
  printf("%.10lf\n", ans);
  return 0;
}
