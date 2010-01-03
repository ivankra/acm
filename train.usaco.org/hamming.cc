/*
ID: infnty1
PROB: hamming
LANG: C++
*/
#include <cstdio>
#include <cstring>
#include <cstdlib>

int N, B, D, A[1024], nbits[1024];

void rec(int k) {
	if (k == N) {
		for (int i = 0; i < N; i += 10) {
			for (int j = 0; j < 10 && i+j < N; j++)
				printf(j ? " %d" : "%d", A[i+j]);
			printf("\n");
		}
		exit(0);
	}

	for (A[k] = 0; A[k] < (1 << B); A[k]++) {
		for (int i = 0; i < k; i++)
			if (nbits[A[k] ^ A[i]] < D) goto skip;
		rec(k+1);
skip:;
	}
}

int main() {
	freopen("hamming.in", "r", stdin);
	freopen("hamming.out", "w", stdout);

	scanf("%d %d %d", &N, &B, &D);

	nbits[0] = 0;
	for (int x = 1; x < 1024; x++)
		nbits[x] = 1 + nbits[x & (x - 1)];

	rec(0);
}
