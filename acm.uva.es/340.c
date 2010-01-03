#include <stdio.h>
#include <string.h>

int a[1024], b[1024], ac[10], bc[10], n;

int main()
{
	int i, j, k, t;

	for (t = 1; scanf("%d", &n) == 1 && n > 0; t++) {
		printf("Game %d:\n", t);

		for (i = 0; i < n; i++)
			scanf("%d", &a[i]);

		memset(ac, 0, sizeof(ac));
		for (i = 0; i < n; i++)
			ac[a[i]]++;

		for (;;) {
			for (i = 0; i < n; i++)
				scanf("%d", &b[i]);

			if (b[0] == 0)
				break;

			memset(bc, 0, sizeof(bc));
			for (i = 0; i < n; i++)
				bc[b[i]]++;

			for (j = 0, i = 0; i < n; i++)
				if (a[i] == b[i]) j++;

			for (k = 0, i = 1; i <= 9; i++)
				k += (bc[i] < ac[i]) ? bc[i] : ac[i];

			printf("    (%d,%d)\n", j, k - j);
		}
	}

	return 0;
}
