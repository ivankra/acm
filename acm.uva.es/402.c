#include <stdio.h>

int main()
{
	static int d[32], s[256], n, x, k, t, r;
	register int i, j;

	for (t = 1; scanf("%d %d", &n, &x) == 2; t++) {
		for (i = 0; i < 20; i++)
			scanf("%d", &d[i]);


		for (i = 0; i < n; i++)
			s[i] = 1;

		for (r = n, k = 0; r > x && k < 20; k++) {
			for (i = 0, j = d[k]; i < n; i++) {
				if (s[i] && --j <= 0) {
					s[i] = 0;
					j = d[k];
					if (--r <= x) break;
				}
			}
		}

		printf("Selection #%d\n", t);
		for (i = 0, j = 0; i < n; i++)
			if (s[i]) printf(j++ ? " %d" : "%d", 1+i);
		printf("\n\n");
	}

	return 0;
}
