// DP, longest common subsequence
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <cmath>
#include <cassert>
#include <algorithm>
#include <vector>
#include <sstream>
#include <iostream>
#include <set>
using namespace std;

char a[100], b[100];
int n, m, lcs[100][100];
vector<string> result;
set<pair<int, string> > seen;

void rec(int i, int j, const string &s) {
	pair<int, string> key(lcs[i][j] > 0 ? i*100+j : 0, s);
	if (seen.count(key) != 0) return;
	seen.insert(key);

	if (lcs[i][j] == 0) {
		result.push_back(s);
	} else if (a[i] == b[j]) {
		rec(i+1, j+1, s+a[i]);
	} else {
		if (lcs[i][j] == lcs[i+1][j]) rec(i+1, j, s);
		if (lcs[i][j] == lcs[i][j+1]) rec(i, j+1, s);
	}
}

int main()
{
	int T;
	scanf("%d", &T);

	for (int cs = 1; cs <= T; cs++) {
		scanf("%s %s", a, b);
		n = strlen(a);
		m = strlen(b);
		memset(lcs, 0, sizeof(lcs));
		for (int i = n-1; i >= 0; i--)
			for (int j = m-1; j >= 0; j--)
				lcs[i][j] = a[i] == b[j] ? 1 + lcs[i+1][j+1] : max(lcs[i+1][j], lcs[i][j+1]);
		result.clear();
		seen.clear();
		rec(0, 0, "");
		sort(result.begin(), result.end());
		for (int i = 0; i < (int)result.size(); i++)
			printf("%s\n", result[i].c_str());
		if (cs != T) printf("\n");
	}
}
