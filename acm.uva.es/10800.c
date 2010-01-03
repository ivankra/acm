#include <stdio.h>
#include <string.h>

int main()
{
	static char buf[64], z[128][64];
	static int n, t, top, bot, w;
	register int i, j, k;

	scanf("%d\n", &n);

	for (t = 1; t <= n && scanf(" %63[CFRcfr]\n", buf) == 1; t++) {
		for (i = 0; buf[i]; i++) buf[i] &= ~0x20;

		memset(z, ' ', sizeof(z));

		for (i = 0, j = 64; buf[i]; i++) {
			if (buf[i] == 'R')
				z[j--][i] = '/';
			else if (buf[i] == 'F')
				z[++j][i] = '\\';
			else
				z[j][i] = '_';
		}

		for (top = 0; top < 128; top++) {
			for (j = 0; j < 64; j++)
				if (z[top][j] != ' ') break;
			if (j < 64) break;
		}

		for (bot = 127; bot >= 0; bot--) {
			for (j = 0; j < 64; j++)
				if (z[bot][j] != ' ') break;
			if (j < 64) break;
		}

		if (top > bot)
			continue;

		printf("Case #%d:\n", t);
		for (i = top, w = 0; i <= bot; i++) {
			printf("| ");
			for (j = 0, k = 0; j < 64; j++)
				if (z[i][j] != ' ') k = j;

			for (j = 0; j <= k; j++)
				putchar(z[i][j]);
			putchar('\n');

			if (k > w)
				w = k;
		}

		printf("+-");
		for (w += 2, i = 0; i < w; i++)
			putchar('-');
		printf("\n\n");
	}

	return 0;
}
