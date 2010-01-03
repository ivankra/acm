#include <stdio.h>
#include <string.h>

int main()
{
	static char m[32][32], s[32][32], buf[2048];
	int i, j, k, t, n, x, y;

	for (scanf("%d\n", &t); t-- > 0;) {
		for (;;) {
			if (gets(buf) == NULL) return 0;
			if (sscanf(buf, "%d", &n) == 1) break;
		}

		memset(m, ' ', sizeof(m));
		memset(s, ' ', sizeof(s));
		while (gets(buf) && sscanf(buf, "%d%d", &y, &x) == 2)
			m[y][x] = 'O';

		while (n-- > 0) {
			for (k = 0; k < 20; k++)
				buf[k] = '*';
			buf[k++] = '\n';

			for (i = 1; i <= 20; i++) {
				for (j = 1; j <= 20; j++)
					buf[k++] = m[i][j];
				//while (buf[k - 1] == ' ') k--;
				buf[k++] = '\n';
			}

			fwrite(buf, 1, k, stdout);

			if (n == 0)
				break;

			for (i = 1; i <= 20; i++) {
				for (j = 1; j <= 20; j++) {
					k = 0;
					if (m[i - 1][j - 1] == 'O') k++;
					if (m[i - 1][j] == 'O') k++;
					if (m[i - 1][j + 1] == 'O') k++;
					if (m[i][j - 1] == 'O') k++;
					if (m[i][j + 1] == 'O') k++;
					if (m[i + 1][j - 1] == 'O') k++;
					if (m[i + 1][j] == 'O') k++;
					if (m[i + 1][j + 1] == 'O') k++;

					if (m[i][j] == 'O') {
						if (k == 2 || k == 3)
							s[i][j] = 'O';
						else
							s[i][j] = ' ';
					} else if (k == 3) {
						s[i][j] = 'O';
					} else {
						s[i][j] = ' ';
					}
				}
			}

			memcpy(m, s, sizeof(m));
		}

		printf("********************\n");
		if (t > 0)
			printf("\n");
	}

	return 0;
}
