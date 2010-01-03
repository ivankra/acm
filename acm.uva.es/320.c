#include <stdio.h>
#include <string.h>

int main()
{
	static char m[32][32];
	int c, x, y, t, n;

	for (scanf("%d", &n), t = 1; t <= n; t++) {
		memset(m, '.', sizeof(m));

		scanf("%d%d", &x, &y);

		while ((c = getchar()) != EOF && c != '.') {
			if (c >= 'a' && c <= 'z')
				c = c - 'a' + 'A';

			if (c == 'E')
				m[y - 1][x++] = 'X';
			else if (c == 'N')
				m[y++][x] = 'X';
			else if (c == 'W')
				m[y][--x] = 'X';
			else if (c == 'S')
				m[--y][x - 1] = 'X';
		}

		printf("Bitmap #%d\n", t);
		for (y = 31; y >= 0; y--) {
			for (x = 0; x < 32; x++)
				putchar(m[y][x]);
			putchar('\n');
		}
		putchar('\n');
	}

	return 0;
}
