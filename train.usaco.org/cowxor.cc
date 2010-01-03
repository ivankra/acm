/*
ID: infnty1
TASK: cowxor
LANG: C++
*/
#include <algorithm>
#include <vector>
#include <iostream>
#include <cstdio>
using namespace std;

int cow[100100], x[100100], N;
bool exists[(1<<22)+100];

int main() {
	freopen("cowxor.in", "r", stdin);
	freopen("cowxor.out", "w", stdout);

	scanf("%d", &N);
	cow[0] = x[0] = 0;
	for (int i = 1; i <= N; i++) {
		scanf("%d", &cow[i]);
		x[i] = x[i-1] ^ cow[i];
	}

	// exists[2^m + a] = true (where 0<=a<2^m), if there exists i, such that
	// the first m bits of 21-bit number x[i] are equal to a.
	memset(exists, 0, sizeof(exists));
	for (int i = 0; i <= N; i++) {
		for (int m = 1; m <= 21; m++) {
			int key = (x[i]>>(21-m)) | (1<<m);
			exists[key] = true;
		}
	}

	int best = 0;
	for (int t = 1; t <= N; t++) {
		int z = 0;
		for (int m = 1; m <= 21; m++) {
			int z1 = z | (1 << (21-m));

			if (exists[((x[t]^z1)>>(21-m)) | (1<<m)]) {
				z = z1;
			}
		}
		best = max(best, z);
	}

	memset(exists, 0, sizeof(exists));

	int bestT;
	for (int t = 0; t <= N; t++) {
		exists[x[t]] = true;
		if (t > 0 && exists[x[t] ^ best]) {
			bestT = t;
			break;
		}
	}

	int bestS;
	for (bestS = bestT; bestS > 1; bestS--)
		if ((x[bestS-1] ^ x[bestT]) == best) break;
	printf("%d %d %d\n", best, bestS, bestT);
}
