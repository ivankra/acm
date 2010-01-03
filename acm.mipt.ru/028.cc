#include <cstdio>

int K, N, m;

int ok() {
	for (int r = N, x = 0; r > K; r--) {
		x = (x + m - 1) % r;
		if (x < K) return 0;
	}
	return 1;
}

int main() {
	scanf("%d", &K);
	N = 2*K;

	for (m = K+1; !ok(); m++);
	printf("%d\n", m);
}
