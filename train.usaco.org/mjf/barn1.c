/*
ID: mjf28791
PROG: barn1
LANG: C
*/
#include <stdio.h>

int main()
{
	int a[256], b[256], r[256], m, s, c, p, i, j;

	freopen("barn1.in", "r", stdin);
	freopen("barn1.out", "w", stdout);

	scanf("%d %d %d", &m, &s, &c);

	for (i = 1; i <= s; i++)
		a[i] = 0;

	while (c-- > 0 && scanf("%d", &p) == 1)
		a[p] = 1;

	for (i = 1; i <= s; i++)
		b[i] = 1;

	for (i = 1; i <= s && a[i] == 0; i++)
		b[i] = 0;

	for (i = s; i >= 1 && a[i] == 0; i--)
		b[i] = 0;

	while (--m > 0) {
		for (i = 1; i <= s; i++) {
			for (r[i] = 0, j = i; j <= s; j++) {
				if (b[j] == 0 || a[j]) break;
				r[i]++;
			}
		}

		for (j = 1, i = 2; i <= s; i++)
			if (r[i] > r[j]) j = i;

		if (r[j] == 0)
			break;

		for (i = 0; i < r[j]; i++)
			b[j + i] = 0;
	}

	for (i = 1, j = 0; i <= s; i++)
		j += b[i];

	printf("%d\n", j);
	return 0;
}
