#include <bits/stdc++.h>
using namespace std;

class EllysReversals {
private:
  vector <pair <char, char> > id[100];
  inline bool equal(const vector <pair <char, char> > &p, const vector <pair <char, char> > &q) {
    if (p.size() != q.size()) return 0;
    for (int i = 0; i < (int)p.size(); i ++)
      if (p[i] != q[i]) return 0;
    return 1;
  }
public:
  inline int getMin(vector <string> words) {
    for (size_t i = 0; i < words.size(); i ++) {
      string &s = words[i];
      int len = s.size();
      if (len & 1) s += "0";
      len = s.size();
      for (int j = 0; j <= len - 2; j += 2) {
        id[i].push_back( make_pair( min(s[j], s[j + 1]), max(s[j], s[j + 1]) ) );
      }
      sort(id[i].begin(), id[i].end());
    }
    sort(id, id + words.size());
    int ans = 0;
    for (int i = 0; i < (int)words.size() - 1; )
      if (equal(id[i], id[i + 1])) i += 2, ans ++;
      else i ++;
    return int(words.size() - ans - ans);
  }
};
