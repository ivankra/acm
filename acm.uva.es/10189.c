#include <stdio.h>
#include <string.h>

int write(int, char *, int);

int main()
{
	static char b[128][128], out[16384];
	int n, m, t, i, j, k;
	char *q;

	for (t = 1; scanf("%d%d", &n, &m) == 2 && n > 0 && m > 0; t++) {
		memset(b, 0, sizeof(b));
		for (i = 1; i <= n && scanf(" %127[.*]", b[i] + 1) == 1; i++);

		sprintf(out, "%sField #%d:\n", (t > 1) ? "\n" : "", t);
		for (q = out; *q; q++);

		for (i = 1; i <= n; i++) {
			for (j = 1; j <= m; j++) {
				if (b[i][j] == '*') {
					*q++ = '*';
				} else {
					k = 0;
					if (b[i - 1][j - 1] == '*') k++;
					if (b[i - 1][j] == '*') k++;
					if (b[i - 1][j + 1] == '*') k++;
					if (b[i][j - 1] == '*') k++;
					if (b[i][j + 1] == '*') k++;
					if (b[i + 1][j - 1] == '*') k++;
					if (b[i + 1][j] == '*') k++;
					if (b[i + 1][j + 1] == '*') k++;
					*q++ = k + '0';
				}
			}
			*q++ = '\n';
		}

		write(1, out, q - out);
	}

	return 0;
}
