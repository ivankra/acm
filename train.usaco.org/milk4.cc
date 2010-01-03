/*
ID: infnty1
PROB: milk4
LANG: C++
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int Q, M, N, P[128];
int f[102][20010], best[128];

void go(int i, int k, int q) {
	if (i >= M || k >= N) return;
	if (best[i] < P[k]) return;

	for (int t = q; t >= 0; t -= P[k]) {
		if (f[k][q] != 1 + f[k+1][t]) continue;

		if (P[k] < best[i]) {
			best[i] = P[k];
			for (int j = i+1; j < M; j++) best[j] = 1<<30;
		}

		go(i+1, k+1, t);
	}

	go(i, k+1, q);
}

int main() {
	freopen("milk4.in", "r", stdin);
	freopen("milk4.out", "w", stdout);

	scanf("%d %d", &Q, &N);
	for (int i = 0; i < N; i++)
		scanf("%d", &P[i]);

	sort(P, P+N);
	N = unique(P, P+N) - P;

	memset(f, 0x3f, sizeof(f));
	f[N][0] = 0;

	for (int k = N-1; k >= 0; k--) {
		for (int q = 0; q <= Q; q++) {
			f[k][q] = 1 + f[k+1][q];
			if (q >= P[k]) f[k][q] <?= f[k][q - P[k]];
		}
		for (int q = 0; q <= Q; q++)
			f[k][q] <?= f[k+1][q];
	}

	M = f[0][Q];
	memset(best, 0x7f, sizeof(best));
	go(0, 0, Q);

	printf("%d", M);
	for (int i = 0; i < M; i++)
		printf(" %d", best[i]);
	printf("\n");
}
