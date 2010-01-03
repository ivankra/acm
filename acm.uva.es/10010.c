#include <stdio.h>

int main()
{
	static char s[64][64], t[256];
	static int dr[8] = {  0,  0,  1,  1,  1, -1, -1, -1 };
	static int dc[8] = {  1, -1,  0,  1, -1,  0,  1, -1 };
	static int m, n, q, r, c, z, d, len;
	register int i, j, k;

	for (scanf("%d", &z); z-- > 0 && scanf("%d %d", &m, &n) == 2;) {
		for (i = 0; i < m && scanf(" %[a-zA-Z]", s[i]) == 1; i++)
			for (j = 0; s[i][j]; j++) s[i][j] |= 0x20;

		for (scanf("%d", &q); q-- > 0 && scanf(" %[A-Za-z]",t) == 1;) {
			for (i = 0; t[i]; i++)
				t[i] |= 0x20;

			for (len = i, r = 0; r < m; r++) {
				for (c = 0; c < n; c++) {
					if (t[0] != s[r][c])
						continue;

					for (d = 0; d < 8; d++) {
						i = r;
						j = c;
						k = 0;

						for (;;) {
							if (k == len) {
								printf("%d %d\n",
								       r+1, c+1);
								goto done;
							}

							if (r < 0 || c < 0 ||
							    r >= m || c >= n ||
							    s[i][j] != t[k])
								break;

							i += dr[d];
							j += dc[d];
							k++;							
						}
					}
				}
			}
			
		done:;

		}

		if (z > 0)
			printf("\n");
	}

	return 0;
}
