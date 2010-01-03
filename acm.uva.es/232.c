#include <stdio.h>
#include <ctype.h>

int a[16][16], b[16][16], w, h, t;

int main()
{
	int i, j, k;

	for (t = 1; scanf("%d %d", &h, &w) == 2 && h > 0; t++) {
		printf("%spuzzle #%d:\n", (t > 1) ? "\n" : "", t);

		for (i = 0; i < h; i++)
			for (j = 0; j < w && (a[i][j] = getchar()) != EOF;)
				if (a[i][j] == '*' || isalpha(a[i][j])) j++;

		for (i = 0, k = 0; i < h; i++)
			for (j = 0; j < w; j++)
				if (a[i][j] != '*' && (i == 0 || j == 0 ||
				    a[i - 1][j] == '*' || a[i][j - 1] == '*'))
					b[i][j] = ++k;
				else
					b[i][j] = 0;

		printf("Across\n");
		for (i = 0; i < h; i++) {
			for (j = 0; j < w; j++) {
				if (a[i][j] == '*') continue;
				if (j != 0 && a[i][j - 1] != '*') continue;
				printf("%3d.", b[i][j]);
				for (k = j; k < w && a[i][k] != '*'; k++)
					putchar(a[i][k]);
				printf("\n");
			}
		}

		printf("Down\n");
		for (i = 0; i < h; i++) {
			for (j = 0; j < w; j++) {
				if (a[i][j] == '*') continue;
				if (i != 0 && a[i - 1][j] != '*') continue;
				printf("%3d.", b[i][j]);
				for (k = i; k < h && a[k][j] != '*'; k++)
					putchar(a[k][j]);
				printf("\n");
			}
		}
	}

	return 0;
}
