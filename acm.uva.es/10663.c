#include <stdio.h>
#include <string.h>
#include <assert.h>

unsigned pmap[32768];
#define P(x) ((pmap[(x) >> 5] >> ((x) & 31)) & 1)

int s[131072], m;

int main()
{
	static int x[1024], n, a, b;
	int i, j;

	memset(pmap, 0, sizeof(pmap));
	for (i = 2; i <= 1000; i++)
		for (j = i * i; j <= 1000000; j *= i)
			pmap[j >> 5] |= 1U << (j & 31);

	while (scanf("%d %d", &a, &b) == 2) {
		s[0] = 0; m = 1;
		for (n = 0;; n++) {
			for (x[n] = n ? (x[n-1] + 1) : a; x[n] <= b; x[n]++) {
				if (P(x[n])) continue;

				for (i = 0; i < m; i++)
					if (P(s[i] + x[n])) break;
				if (i < m) continue;

				break;
			}
			if (x[n] > b) break;

			for (i = m - 1; i >= 0; i--)
				s[m++] = s[i] + x[n];
		}

		for (i = 0; i < n; i++)
			printf(i ? " %d" : "%d", x[i]);
		printf("\n");
	}

	return 0;
}
