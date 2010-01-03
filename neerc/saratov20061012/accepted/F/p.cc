#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cctype>
#include <cassert>
#include <vector>
#include <string>
#include <sstream>
#include <iostream>
using namespace std;
typedef unsigned long long ui64;

int N, M, R;
ui64 usersOf[128][2];
int cnt[128];

int uf[128];

int f(int x) {
	int z = x;
	while (uf[z] != z) z = uf[z];

	while (x != z) {
		int y = uf[x];
		uf[x] = z;
		x = y;
	}

	return z;
}

void u(int x, int y) {
	x = f(x);
	y = f(y);
	if (x == y) return;

	R--;
	uf[x] = y;
}

int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);

	memset(usersOf, 0, sizeof(usersOf));

	scanf("%d %d", &N, &M);
	for (int i = 0; i < M; i++) {
		int k;
		scanf("%d", &k);

		while (k-- > 0) {
			int t;
			scanf("%d", &t);
			t--;

			usersOf[t][i/64] |= 1ULL << (i%64);
			cnt[t]++;
		}
	}

	for (int i = 0; i < N; i++)
		uf[i] = i;
	R = N;

	for (int i = 0; i < N; i++) {
		if (cnt[i] == 0) continue;
		for (int j = i+1; j < N; j++) {
			if (cnt[j] == 0) continue;

			if (usersOf[i][0] == usersOf[j][0] &&
				usersOf[i][1] == usersOf[j][1]) {
//printf("merge resources %d, %d\n", i+1, j+1);
					u(i, j);
			}
		}
	}

	for (int i = 0; i < N; i++) {
		if (cnt[i] == 0) R--;
	}

	printf("%d\n", R);
	return 0;
}