#include <algorithm>
#include <vector>
#include <sstream>
#include <iostream>
#include <cstdio>
#include <cmath>
#include <cctype>
#include <cassert>
#include <map>
using namespace std;
typedef long long int64;

bool byLength(const string &a, const string &b) {
	if (a.size() != b.size()) return a.size() < b.size();
	return a < b;
}

struct PotsPyramids {
	vector<string> findLongestPyramidLine(vector<string> a) {
		int N = a.size();
		sort(a.begin(), a.end(), byLength);

		vector<string> orig = a;
		for (int i = 0; i < N; i++) sort(a[i].begin(), a[i].end());

		map<string, int> revmap;
		for (int i = 0; i < N; i++)
			revmap[a[i]] = i;

		vector<int> f(N, 0), prev(N, 0);
		for (int i = 0; i < N; i++) {
			f[i] = 1;
			prev[i] = i;
		}
		
		for (int i = 0; i < N; i++) {
			for (char c = 'A'; c <= 'Z'; c++) {
				string s = a[i] + (char)c;
				sort(s.begin(), s.end());
				if (revmap.count(s) > 0) {
					int j = revmap[s];
					if (f[i]+1 > f[j]) {
						f[j] = f[i] + 1;
						prev[j] = i;
					}
				}
			}
		}

		int maxAt = 0;
		for (int i = 0; i < N; i++)
			if (f[i] > f[maxAt]) maxAt = i;

		vector<string> res;
		for (int m = f[maxAt], x = maxAt; m >= 1; x = prev[x], m--)
			res.push_back(orig[x]);
		reverse(res.begin(), res.end());
		return res;
	}
};
