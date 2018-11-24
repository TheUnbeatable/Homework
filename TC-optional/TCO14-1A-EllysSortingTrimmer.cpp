#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <string>
using namespace std;

class EllysSortingTrimmer {
private:
  char s[100];
public:
  inline string getMin(string S, int L) {
    int n = S.length();
    for (int i = 0; i < n; i ++) s[i + 1] = S[i];
    for (int i = n; i - L + 1 >= 1; i --) sort(s + i - L + 1, s + i + 1);
    string ans;
    for (int i = 1; i <= L; i ++) ans += s[i];
    return ans;
  }
};
