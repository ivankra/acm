#include <stdio.h>

int main()
{
	unsigned long long r;
	int t, m, i, j, k, n;
	static char buf[256];

	for (scanf("%d", &m), t = 1; t <= m && scanf(" %[A-Z]",buf)==1; t++) {
		for (r = 1, i = 0; buf[i]; r *= (unsigned long long)++i);
		n = i;

		for (i = 0; i < n; i++) {
			if (buf[i] == 0) continue;
			for (k = 1, j = i + 1; j < n; j++)
				if (buf[j] == buf[i]) {
					buf[j] = 0;
					r /= (unsigned long long)++k;
				}
		}

		printf("Data set %d: %lld\n", t, r);
	}

	return 0;
}
