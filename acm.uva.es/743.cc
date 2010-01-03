#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <cmath>
#include <cassert>
#include <algorithm>
#include <vector>
#include <iostream>
#include <sstream>
using namespace std;

string NA = "NOT ACCEPTABLE";

string mtm(string s) {
	if (find(s.begin(), s.end(), '0') != s.end()) return NA;

	int k = 0;
	while (k < (int)s.size() && s[k] == '3') k++;

	s = s.substr(k);
	if ((int)s.size() <= 1 || s[0] != '2') return NA;

	s = s.substr(1);
	while (k-- > 0)
		s = s + "2" + s;
	return s;
}

int main() {
	string s;

	while (cin >> s) {
		if (s == "0") break;
		cout << mtm(s) << endl;
	}
}
