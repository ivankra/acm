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
using namespace std;

int main() {
	static int a[11000], T;
	scanf("%d", &T);

	for (int cs = 1; cs <= T; cs++) {
		memset(a, 0, sizeof(a));
		for (int i = 0; i < 3; i++) {
			int n, x;
			scanf("%d", &n);
			for (int j = 0; j < n; j++) {
				scanf("%d", &x);
				a[x] |= 1 << i;
			}
		}

		int m = 0;
		vector<int> v[3];

		for (int i = 0; i < 3; i++) {
			for (int j = 0; j <= 10000; j++)
				if (a[j] == (1 << i)) v[i].push_back(j);
			m >?= v[i].size();
		}

		printf("Case #%d:\n", cs);
		for (int i = 0; i < 3; i++) {
			if (v[i].size() == m) {
				printf("%d %d", i+1, v[i].size());
				for (int j = 0; j < v[i].size(); j++) printf(" %d", v[i][j]);
				printf("\n");
			}
		}
	}
}
