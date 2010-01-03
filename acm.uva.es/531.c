#include <stdio.h>
#include <string.h>

static int dictlen, lwr[256];
static char dict[256][64];

static int readw()
{
	static char buf[1024];
	register int k, c;

	for (k = 0; (c = getchar()) != EOF;) {
		if (lwr[c] != 0) {
			buf[k++] = lwr[c];
		} else if (c == '#') {
			if (k) {
				ungetc(c, stdin);
				break;
			}
			return 0;
		} else if (k != 0) {
			break;
		}
	}

	if (k == 0)
		return -1;

	buf[k] = '\0';

	for (k = 1; k <= dictlen; k++)
		if (strcmp(dict[k], buf) == 0) return k;

	strcpy(dict[++dictlen], buf);
	return dictlen;
}

int main()
{
	static int a[128], b[128], tab[128][128], lcs[128];
	register int i, j, m, n, k;

	for (i = 0; i < 256; i++)
		lwr[i] = ((i >= 'A' && i <= 'Z') ? (i - 'A' + 'a') :
			  ((i >= 'a' && i <= 'z') ? i : 0));

	for (;;) {
		dictlen = 0;

		for (m = 0, a[0] = 0; (i = readw()) > 0;)
			a[++m] = i;

		if (i < 0)
			break;

		for (n = 0, b[0] = 0; (i = readw()) > 0;)
			b[++n] = i;

		for (i = 0; i < 128; i++)
			tab[0][i] = 0;

		for (i = 1; i <= m; i++) {
			tab[i][0] = 0;
			for (j = 1; j <= n; j++) {
				if (a[i] == b[j])
					tab[i][j] = tab[i - 1][j - 1] + 1;
				else if (tab[i][j - 1] >= tab[i - 1][j])
					tab[i][j] = tab[i][j - 1];
				else
					tab[i][j] = tab[i - 1][j];
			}
		}

		for (i = m, j = n, k = 0; i > 0 && j > 0;) {
			if (a[i] == b[j]) {
				lcs[k++] = a[i];
				i--;
				j--;
			} else if (tab[i - 1][j] >= tab[i][j - 1]) {
				i--;
			} else {
				j--;
			}
		}

		for (i = 0; k > 0;)
			printf((i++ == 0) ? "%s" : " %s", dict[lcs[--k]]);
		printf("\n");
	}

	return 0;
}
