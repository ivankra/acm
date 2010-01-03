#include <stdio.h>

int main()
{
	static int d[32][32], p[32][32], u[32], n, m, c;
	static char s[1024], t[1024];
	register int i, j, k;

	for (scanf("%d", &c); c-- > 0 && scanf("%d %d", &n, &m) == 2;) {
		for (i = 0; i < 26; i++) {
			for (u[i] = 0, j = 0; j < 26; j++) {
				d[i][j] = 0x3FFFFFFF;
				p[i][j] = j;
			}
			d[i][i] = 0;
		}

		while (n-- > 0 && scanf(" %[A-Za-z] %[A-Za-z]", s, t) == 2) {
			i = s[0] - 'A';
			j = t[0] - 'A';
			u[i] = u[j] = 1;
			d[i][j] = d[j][i] = 1;
		}

		for (k = 0; k < 26; k++) {
			if (u[k] == 0)
				continue;

			for (i = 0; i < 26; i++) {
				if (d[i][k] == 0x3FFFFFFF)
					continue;

				for (j = 0; j < i; j++) {
					if ((d[i][k] + d[k][j]) >= d[i][j])
						continue;

					d[j][i] = d[i][j] = d[i][k] + d[k][j];
					p[i][j] = p[i][k];
					p[j][i] = p[j][k];
				}
			}
		}

		while (m-- > 0 && scanf(" %[A-Za-z] %[A-Za-z]", s, t) == 2) {
			i = s[0] - 'A';
			j = t[0] - 'A';

			for (k = 0;;) {
				s[k++] = i + 'A';

				if (i == j)
					break;

				i = p[i][j];
			}

			s[k++] = '\n';

			fwrite(s, 1, k, stdout);
		}

		if (c > 0)
			printf("\n");
	}

	return 0;
}
