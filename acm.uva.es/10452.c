#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main()
{
	static char s[16][16], w[] = "IEHOVA#";
	int i, j, k, m, n, c, t, x, y;

	for (scanf("%d", &t); t-- > 0 && scanf("%d %d", &m, &n) == 2;) {
		memset(s, 0, sizeof(s));

		for (k = 0, i = 1; i <= m; i++)
			for (j = 1; j <= n && (c = getchar()) != EOF;)
				if (isalpha(c) || c == '@' || c == '#')
					s[i][j++] = c;

		for (i = 1, x = y = 0; i <= m; i++) {
			for (j = 1; j <= n; j++) {
				if (s[i][j] == '@') {
					y = i;
					x = j;
				}
			}
			if (j <= n) break;
		}

		for (k = 0; w[k] && y > 0 && x > 0; k++) {
			if (s[y][x - 1] == w[k]) {
				printf(k ? " left" : "left");
				x--;
			} else if (s[y][x + 1] == w[k]) {
				printf(k ? " right" : "right");
				x++;
			} else {
				printf(k ? " forth" : "forth");
				y--;
			}
		}

		printf("\n");
	}

	return 0;
}
