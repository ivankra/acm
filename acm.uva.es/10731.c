#include <stdio.h>
#include <string.h>
#include <ctype.h>

int a[32], d[32][32];

void parse()
{
	int x[8], i, c;

	for (i = 0; i < 6 && (c = getchar()) != EOF;)
		if (isalpha(c)) x[i++] = toupper(c) - 'A';

	for (i = 0; i < 5; i++) {
		a[x[i]] = 1;
		if (x[i] != x[5]) d[x[i]][x[5]] = 1;
	}
}

int main()
{
	int i, j, k, n, t;

	for (t = 0; scanf("%d", &n) == 1 && n > 0;) {
		if (t++) printf("\n");

		memset(d, 0, sizeof(d));
		memset(a, 0, sizeof(a));

		while (n-- > 0)
			parse();

		for (k = 0; k < 26; k++)
			for (i = 0; i < 26; i++)
				if (d[i][k])
					for (j = 0; j < 26; j++)
						d[i][j] |= d[k][j];

		for (k = 0; k < 26; k++) {
			if (a[k] == 0) continue;

			printf("%c", k + 'A');
			a[k] = 0;

			for (i = 0; i < 26; i++) {
				if (a[i] && d[k][i] && d[i][k]) {
					printf(" %c", i + 'A');
					a[i] = 0;
				}
			}

			printf("\n");
		}
	}

	return 0;
}
