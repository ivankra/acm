#include <stdio.h>

int main()
{
	static int order[256], tree[1024], val[256], n, m, t;
	int i, j;

	for (t = 1; scanf("%d", &n) == 1 && n > 0; t++) {
		for (i = 0; i < n && scanf(" x %d", &order[i]) == 1; i++)
			order[i]--;

		for (i = 0; i < (1 << n) && (j = getchar()) != EOF;)
			if (j == '0' || j == '1') tree[i++] = j;

		printf("S-Tree #%d:\n", t);

		for (scanf("%d", &m); m-- > 0;) {
			for (i = 0; i < n && (j = getchar()) != EOF;)
				if (j == '0' || j == '1') val[i++] = j - '0';


			for (i = 0, j = 0; i < n; i++)
				j = (j << 1) | val[order[i]];

			putchar(tree[j]);
		}

		printf("\n\n");
	}

	return 0;
}
