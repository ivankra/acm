#include <stdio.h>

#define MAXDIG 1536

static unsigned char tab[1024][MAXDIG];
static int ndig[1024];

static void maketab()
{
	int i, c, m, n;

	memset(tab, 0, sizeof(tab));

	tab[0][0] = 1; ndig[0] = 1;
	tab[1][0] = 2; ndig[1] = 1;
	tab[2][0] = 5; ndig[2] = 1;

	for (n = 3; n <= 1000; n++) {
		m = ndig[n - 1];
		for (i = 0, c = 0; i < m; i++) {
			c += 2 * tab[n - 1][i] + tab[n - 2][i] + tab[n - 3][i];
			tab[n][i] = (c % 10);
			c /= 10;
		}

		for (; c != 0;) {
			tab[n][i++] = (c % 10);
			c /= 10;
		}

		ndig[n] = i;
	}
}

int main()
{
	static char buf[4096];
	static int n;
	register int i, j;

	maketab();

	while (scanf("%d", &n) == 1) {
		for (i = 0, j = ndig[n] - 1; j >= 0; j--)
			buf[i++] = tab[n][j] + '0';
		buf[i] = '\0';

		printf("%s\n", buf);
	}

	return 0;
}
