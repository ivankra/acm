#include <stdio.h>
#include <string.h>

static char names[16][16], s[16];
static int profit[16], n, m, k, t;

int main()
{
	int i, j, r;

	for (t = 0; scanf("%d", &n) == 1; t++) {
		for (i = 0; i < n; i++)
			scanf(" %[A-Za-z]", names[i]);

		for (i = 0; i < n; i++)
			profit[i] = 0;

		for (r = 0; r < n; r++) {
			scanf(" %[A-Za-z] %d %d", s, &m, &k);
			for (i = 0; i < n; i++)
				if (strcmp(names[i], s) == 0) break;

			if (k == 0) {
				continue;
			}

			profit[i] = profit[i] - m + (m % k);
			m /= k;

			while (k-- > 0 && scanf(" %[A-Za-z]", s) == 1) {
				for (j = 0; j < n; j++) {
					if (strcmp(names[j], s) == 0) {
						profit[j] += m;
						break;
					}
				}
			}
		}

		if (t > 0)
			printf("\n");

		for (i = 0; i < n; i++)
			printf("%s %d\n", names[i], profit[i]);
	}

	return 0;
}
