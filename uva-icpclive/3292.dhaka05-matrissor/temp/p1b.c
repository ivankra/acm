/* ok; with assert(strlen ... < 5) crashes */
#include <stdio.h>
#include <string.h>
#include <assert.h>

int R[64], C[64], n;

int main()
{
	static char buf[65536];
	int i, j, t, T, q;

	for (scanf("%d", &T), t = 1; t <= T && scanf("%d", &n) == 1; t++) {
		assert(2 <= n && n <= 50);

		for (i = 0; i < n; i++) {
			scanf("%d %d", &R[i], &C[i]);
			assert(1 <= R[i] && R[i] <= 50);
			assert(1 <= C[i] && C[i] <= 50);
		}

		for (i = 1; i < n; i++)
			assert(C[i - 1] == R[i]);

		for (scanf("%d", &q); q-- > 0;) {
			scanf("%s", buf);
			for (j = 0; buf[j] == '0'; j++);
			assert(strlen(buf + j) < 10);
		}
	}

	return 0;
}
