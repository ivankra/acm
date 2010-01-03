#include <stdio.h>
#include <string.h>

int main()
{
	static int a[128][128], b[128][128], u[128], t, m;
	static char x, y;
	register int i, j, k;

	for (scanf("%d", &t); t-- > 0;) {
		memset(a, '\0', sizeof(a));
		memset(b, '\0', sizeof(b));

		for (i = 0; i < 128; i++)
			a[i][i] = b[i][i] = 1;

		scanf("%d", &m);

		memset(u, '\0', sizeof(u));
		while (m-- > 0 && scanf(" %c %c", &x, &y) == 2) {
			a[x][y] = 1;
			u[x] = u[y] = 1;
		}

		for (k = 0; k < 128; k++) {
			if (u[k] == 0) continue;
			for (i = 0; i < 128; i++) {
				if (a[i][k] == 0 || i == k) continue;
				for (j = 0; j < 128; j++)
					a[i][j] |= a[k][j];
			}
		}

		scanf("%d", &m);

		memset(u, '\0', sizeof(u));
		while (m-- > 0 && scanf(" %c %c", &x, &y) == 2) {
			b[x][y] = 1;
			u[x] = u[y] = 1;
		}

		for (k = 0; k < 128; k++) {
			if (u[k] == 0) continue;
			for (i = 0; i < 128; i++) {
				if (b[i][k] == 0 || i == k) continue;
				for (j = 0; j < 128; j++)
					b[i][j] |= b[k][j];
			}
		}

		printf("%s\n%s",
			(memcmp(a, b, sizeof(a)) == 0) ? "YES" : "NO",
			(t > 0) ? "\n" : ""
		);
	}

	return 0;
}
