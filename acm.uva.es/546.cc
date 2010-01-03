#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include <cctype>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>
#include <map>
using namespace std;
typedef vector<int> VI;
typedef vector<VI> VVI;

vector<int> split(const string &s) {
	vector<int> res;
	for (int i = 0; i < s.size();) {
		if (!isdigit(s[i]) && s[i] != '-') {
			i++;
		} else {
			int sign = s[i] == '-' ? -1 : +1;
			if (s[i] == '-') i++;
			res.push_back(0);
			while (i < s.size() && isdigit(s[i])) {
				res.back() = res.back() * 10 + s[i] - '0';
				i++;
			}
			res.back() *= sign;
		}
	}
	return res;
}

int eval(VVI &a, VVI &b, int y, int x)
{
	int res = 0;
	for (int i = 0; i < b.size(); i++)
		for (int j = 0; j < b[0].size(); j++)
			res += a[y+i][x+j] * b[i][j];
	return res;
}

int main()
{
	string s;
	getline(cin, s);
	while (s.size() > 0 && s[0] != 'F') {
		VVI a, b;
		assert(s[0] == 'I');
		while (getline(cin, s) && !isalpha(s[0])) {
			a.push_back(split(s));
			if (a.size() >= 2) assert(a[0].size() == a.back().size());
		}

		assert(s[0] == 'T');
		while (getline(cin, s) && !isalpha(s[0])) {
			b.push_back(split(s));
			if (b.size() >= 2) assert(b[0].size() == b.back().size());
		}

		int bestY = 0, bestX = 0, best = -(1<<30);
		for (int y = 0; y + b.size() <= a.size(); y++) {
			for (int x = 0; x + b[0].size() <= a[0].size(); x++) {
				int f = eval(a, b, y, x);
				if (f < best) continue;
				if (f == best) {
					if (bestY < y) continue;
					if (bestY == y && bestX < x) continue;
				}
				best = f; bestY = y; bestX = x;
			}
		}
		printf("(%d,%d)\n", bestX, bestY);
	}
}
