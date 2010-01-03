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

int mat[128][128], a[128], N;

int linear() {
	int ma = a[0], mi = a[0], sum = 0;
	for (int k = 0, s_ma = 0, s_mi = 0; k < N; k++) {
		s_ma = (s_ma < 0 ? 0 : s_ma) + a[k];
		s_mi = (s_mi > 0 ? 0 : s_mi) + a[k];
		if (s_ma > ma) ma = s_ma;
		if (s_mi < mi) mi = s_mi;
		sum += a[k];
	}
	return max(ma, sum-mi);
}

int main() {
	int T;
	scanf("%d", &T);

	for (int cs = 1; cs <= T && scanf("%d", &N) == 1; cs++) {
		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
				scanf("%d", &mat[i][j]);

		int best = mat[0][0];
		for (int i = 0; i < N; i++) {
			for (int k = 0; k < N; k++) a[k] = 0;
			for (int j = i;;) {
				for (int k = 0; k < N; k++) a[k] += mat[j][k];
				best = max(best, linear());
				if (++j >= N) j = 0;
				if (j == i) break;
			}
		}
		printf("%d\n", best);
	}
}
