#include <stdio.h>

int main()
{
	static int a[128], b[128], buf1[128], buf2[128], *p, *q, n, m, t;
	register int i, j;

	for (t = 1; scanf("%d %d", &n, &m) == 2 && (n | m) != 0; t++) {
		for (i = 1; i <= n; i++)
			scanf("%d", &a[i]);

		for (i = 1; i <= m; i++)
			scanf("%d", &b[i]);


		for (i = 0; i <= m; i++)
			buf1[i] = buf2[i] = 0;

		for (p = buf1, q = buf2, i = 1; i <= n; i++) {
			q[0] = 0;
			for (j = 1; j <= m; j++) {
				if (a[i] == b[j])
					q[j] = p[j - 1] + 1;
				else if (p[j] > q[j - 1])
					q[j] = p[j];
				else
					q[j] = q[j - 1];
			}

			p = q;
			q = (q == buf1) ? buf2 : buf1;
		}

		printf("Twin Towers #%d\nNumber of Tiles : %d\n\n", t, p[m]);
	}

	return 0;
}
