#include <stdio.h>

static int a[12000], n;

static void sol()
{
	register int i, j;
	static int s;

	for (s = 0;;) {
		for (i = 1, j = 0; i <= n; i++) {
			if (a[i] == 0 || a[i] == i)
				continue;

			if (a[a[i]] == 0) {
				printf("%d %d\n", i, a[i]);
				a[a[i]] = a[i];
				a[i] = 0;
				s++;
				j = -1;
			}

			if (j == 0)
				j = i;
		}

		if (i > n && j == 0)
			break;

		if (j < 0)
			continue;

		for (i = n; i > 0 && a[i] != 0; i--);

		printf("%d %d\n", j, i);
		a[i] = a[j];
		a[j] = 0;
		s++;
	}

	if (s == 0)
		printf("No optimization needed\n");
}

int main()
{
	int t, k, m, p, i;

	for (scanf("%d", &t); t-- > 0 && scanf("%d %d", &n, &k) == 2;) {
		for (i = 1; i <= n; i++)
			a[i] = 0;

		for (i = 0; k-- > 0 && scanf("%d", &m) == 1;)
			while (m-- > 0 && scanf("%d", &p) == 1) a[p] = ++i;

		sol();

		if (t) printf("\n");
	}

	return 0;
}
