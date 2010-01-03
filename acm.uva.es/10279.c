#include <stdio.h>
#include <string.h>

int main()
{
	static char m[16][16], r[16][16], buf[4096];
	static int t, n;
	int i, j, c;

	for (scanf("%d", &t); t-- > 0 && scanf("%d", &n) == 1;) {
		memset(m, 0, sizeof(m));
		for (i = 1; i <= n; i++)
			for (j = 1; j <= n && (c = getchar()) != EOF;)
				if (c == '.')
					j++;
				else if (c == '*')
					m[i][j++] = 1;

		for (i = 1; i <= n; i++)
			for (j = 1; j <= n && (c = getchar()) != EOF;)
				if (c == '.' || c == 'x')
					r[i][j++] = c;

		for (c = 0, i = 1; i <= n; i++) {
			for (j = 1; j <= n; j++) {
				if (r[i][j] == '.')
					continue;

				if (m[i][j]) {
					c = 1;
					continue;
				}

				r[i][j] = (m[i - 1][j - 1] + m[i - 1][j] +
					   m[i - 1][j + 1] + m[i][j - 1] +
					   m[i][j + 1] + m[i + 1][j - 1] +
					   m[i + 1][j] + m[i + 1][j + 1] +
					   '0');
			}
		}

		if (c)
			for (i = 1; i <= n; i++)
				for (j = 1; j <= n; j++)
					if (m[i][j]) r[i][j] = '*';

		for (c = 0, i = 1; i <= n; i++) {
			for (j = 1; j <= n; j++)
				buf[c++] = r[i][j];
			buf[c++] = '\n';
		}

		if (t > 0)
			buf[c++] = '\n';

		buf[c] = '\0';

		printf("%s", buf);
	}

	return 0;
}
