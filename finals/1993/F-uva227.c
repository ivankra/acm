#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main()
{
	static char a[8][8];
	int i, c, t, x, y;

	for (t = 1;; t++) {
		for (i = x = 0; i < 25 && (c = getchar()) != EOF;) {
			if (c == ' ') {
				x = i++;
			} else if (isalpha(c)) {
				a[i / 5][i % 5] = c;
				i++;
			}
		}

		if (i < 25 || a[0][0] == 'Z')
			break;

		y = x / 5;
		x %= 5;

		printf("%sPuzzle #%d:\n", (t > 1) ? "\n" : "", t);

		while ((c = getchar()) != EOF && c != '0') {
			c = toupper(c);

			if (c == 'A') {
				if (y == 0) break;
				a[y][x] = a[y - 1][x];
				y--;
			} else if (c == 'B') {
				if (y == 4) break;
				a[y][x] = a[y + 1][x];
				y++;
			} else if (c == 'L') {
				if (x == 0) break;
				a[y][x] = a[y][x - 1];
				x--;
			} else if (c == 'R') {
				if (x == 4) break;
				a[y][x] = a[y][x + 1];
				x++;
			}
		}

		if (c != '0') {
			while ((c = getchar()) != EOF && c != '0');
			printf("This puzzle has no final configuration.\n");
			continue;
		}

		a[y][x] = ' ';

		for (y = 0; y < 5; y++)
			for (x = 0; x < 5; x++)
				printf((x == 4) ? "%c\n" : "%c ", a[y][x]);

	}

	return 0;
}
