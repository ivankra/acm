#include <stdio.h>

char name[32][128];
int tab[16][16];

double win[16][16];

int main()
{
	int i, j, k, c, r;

	for (i = 0; i < 16; i++)
		gets(name[i]);

	for (i = 0; i < 16; i++)
		for (j = 0; j < 16; j++)
			scanf("%d", &tab[i][j]);

	for (i = 0; i < 16; i++)
		for (j = 0; j < 16; j++)
			win[i][j] = 0;

	for (i = 0; i < 16; i++)
		win[i][0] = 1;

	for (r = 1; r <= 4; r++) {
		for (c = 0; c < 16; c++) {
			win[c][r] = 0;

			i = c & ~((1 << r) - 1);
			for (k = (1 << r); k-- > 0; i++)
				if (((i >> (r - 1)) & 1) != (((c >> (r - 1)) & 1)))
					win[c][r] += win[i][r - 1] * tab[c][i] / 100.0;

			win[c][r] *= win[c][r - 1];
		}
	}

	for (i = 0; i < 16; i++)
		printf("%-10s p=%.2f%%\n", name[i], win[i][4] * 100.0);

	return 0;
}
