#include <stdio.h>
#include <string.h>

#define HSIZE	1048576
#define	HDIV	533879

int htab[HDIV], hx[HSIZE], hy[HSIZE], hnext[HSIZE], count, prev;

void add(int x, int y)
{
	int i;
	unsigned h;

	h = x * 36457 + y;
	h %= HDIV;

	for (i = htab[h]; i != 0; i = hnext[i])
		if (hx[i] == x && hy[i] == y) return;

	i = ++count;
	hx[i] = x;
	hy[i] = y;
	hnext[i] = htab[h];
	htab[h] = i;
}

int main()
{
	static int x[1024], y[1024], k[1024], n, t;
	int i, m;

	while (scanf("%d", &n) == 1 && n > 0) {
		for (i = 0; i < n; i++)
			scanf("%d %d %d", &x[i], &y[i], &k[i]);

		for (i = 0, m = k[0]; i < n; i++)
			if (k[i] > m) m = k[i];

		memset(htab, 0, sizeof(htab));
		for (count = prev = 0; m >= 0; m--) {
			t = count;
			for (i = count; i > prev; i--) {
				add(hx[i] + 1, hy[i] + 2);
				add(hx[i] + 1, hy[i] - 2);
				add(hx[i] - 1, hy[i] + 2);
				add(hx[i] - 1, hy[i] - 2);
				add(hx[i] + 2, hy[i] + 1);
				add(hx[i] + 2, hy[i] - 1);
				add(hx[i] - 2, hy[i] + 1);
				add(hx[i] - 2, hy[i] - 1);
			}
			prev = t;

			for (i = 0; i < n; i++)
				if (k[i] == m) add(x[i], y[i]);
		}

		printf("%d\n", count);
	}

	return 0;
}
