#include <stdio.h>

int main()
{
	static int t, c, e, p, map[676], d[32][32], n;
	static char a[16], b[16];
	register int i, j, k;

	printf("SHIPPING ROUTES OUTPUT\n");
	scanf("%d", &c);

	for (t = 1; t <= c && scanf("%d %d %d", &n, &e, &p) == 3; t++) {
		printf("\nDATA SET %2d\n\n", t);

		for (i = 0; i < n && scanf(" %[A-Z]", a) == 1; i++)
			map[(a[0] - 'A') * 26 + a[1] - 'A'] = i;

		for (i = 0; i < n; i++) {
			for (j = 0; j < n; j++)
				d[i][j] = 0xFFFF;
			d[i][i] = 0;
		}

		while (e-- > 0 && scanf(" %[A-Z] %[A-Z]", a, b) == 2) {
			i = map[(a[0] - 'A') * 26 + a[1] - 'A'];
			j = map[(b[0] - 'A') * 26 + b[1] - 'A'];

			if (i != j)
				d[i][j] = d[j][i] = 1;
		}

		if (p == 0)
			continue;

		for (k = 0; k < n; k++) {
			for (i = 0; i < n; i++) {
				if (k == i || d[i][k] == 0xFFFF)
					continue;

				for (j = 0; j < i; j++) {
					if ((d[i][k] + d[k][j]) >= d[i][j])
						continue;

					d[i][j] = d[j][i] = d[i][k] + d[k][j];
				}
			}
		}

		while (p-- > 0 && scanf(" %d %[A-Z] %[A-Z]", &e, a, b) == 3) {
			i = map[(a[0] - 'A') * 26 + a[1] - 'A'];
			j = map[(b[0] - 'A') * 26 + b[1] - 'A'];

			if (d[i][j] == 0xFFFF)
				printf("NO SHIPMENT POSSIBLE\n");
			else
				printf("$%d\n", e * d[i][j] * 100);
		}
	}

	printf("\nEND OF OUTPUT\n");
	return 0;
}
