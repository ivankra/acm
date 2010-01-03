#include <stdio.h>
#include <string.h>
#include <ctype.h>

char a[128][128], b[128][128];
int r, c;

void evolve()
{
	int i, j;

	for (i = 1; i <= r; i++) {
		for (j = 1; j <= c; j++) {
#define ADJ(w) (a[i - 1][j] == w || a[i + 1][j] == w || a[i][j - 1] == w || a[i][j + 1] == w)
			if (a[i][j] == 'R') {
				b[i][j] = ADJ('P') ? 'P' : 'R';
			} else if (a[i][j] == 'S') {
				b[i][j] = ADJ('R') ? 'R' : 'S';
			} else {
				b[i][j] = ADJ('S') ? 'S' : 'P';
			}
#undef ADJ
		}
	}

	for (i = 1; i <= r; i++)
		for (j = 1; j <= c; j++)
			a[i][j] = b[i][j];
}

int main()
{
	int i, j, k, n, t;

	for (scanf("%d", &t); t-- > 0 && scanf("%d %d %d", &r, &c, &n) == 3;) {
		memset(a, 0, sizeof(a));
		for (i = 1; i <= r; i++)
			for (j = 1; j <= c && (k = getchar()) != EOF;)
				if (isalpha(k)) a[i][j++] = k;

		while (n-- > 0)
			evolve();

		for (i = 1; i <= r; i++) {
			for (j = 1; j <= c; j++) putchar(a[i][j]);
			printf("\n");
		}

		if (t > 0) printf("\n");
	}

	return 0;
}
