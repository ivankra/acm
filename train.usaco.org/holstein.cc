/*
ID: infnty1
PROB: holstein
LANG: C++
*/
#include <cstdio>

int nbits(int x) {
	int n = 0;
	for (; x > 0; n++) x &= x-1;
	return n;
}

int main() {
	freopen("holstein.in", "r", stdin);
	freopen("holstein.out", "w", stdout);

	int V, req[30];

	scanf("%d", &V);
	for (int i = 0; i < V; i++) scanf("%d", &req[i]);

	int G, A[15][30];
	scanf("%d", &G);
	for (int i = 0; i < G; i++)
		for (int j = 0; j < V; j++)
			scanf("%d", &A[i][j]);

	int bestn = 999, best = 0;
	for (int x = 0; x < (1 << G); x++) {
		if (nbits(x) >= bestn) continue;

		int t[30];
		for (int i = 0; i < V; i++) t[i] = 0;

		for (int i = 0; i < G; i++)
			if (x & (1 << i))
				for (int j = 0; j < V; j++) t[j] += A[i][j];

		int okay = 1;
		for (int i = 0; i < V; i++)
			if (t[i] < req[i]) okay = 0;

		if (okay) bestn = nbits(best = x);
	}

	printf("%d", bestn);
	for (int i = 0; i < G; i++)
		if (best & (1 << i)) printf(" %d", i+1);
	printf("\n");

	return 0;
}
