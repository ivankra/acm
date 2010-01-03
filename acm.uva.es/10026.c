#include <stdio.h>

int main()
{
	static struct { int r, s, t; } a[1024];
	int i, j, t, n, x, y;

	for (scanf("%d", &t); t-- > 0 && scanf("%d", &n) == 1;) {
		for (i = 0; i < n && scanf("%d %d", &x, &y) == 2; i++) {
			for (j = i - 1; j >= 0 && a[j].t * y > a[j].s * x; j--)
				a[j + 1] = a[j];

			j++;
			a[j].t = x;
			a[j].s = y;
			a[j].r = i + 1;
		}

		for (i = 0; i < n; i++)
			printf(((i + 1) < n) ? "%d " : "%d\n", a[i].r);

		if (t) printf("\n");
	}

	return 0;
}
