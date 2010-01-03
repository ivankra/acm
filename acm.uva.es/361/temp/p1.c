#include <stdio.h>

typedef struct {
	int x[256], y[256], n;
} hull_t;

int inside(hull_t *a, int x, int y)
{
	int i, t;

	if (a->n < 3)
		return 0;

	for (i = 0; i < a->n; i++) {
		t = (a->x[i] - x) * (a->y[i + 1] - y) - (a->x[i + 1] - x) * (a->y[i] - y);
		if (t < 0)
			return 0;
	}

	return 1;
}

void hull(hull_t *a, int x[], int y[], int n)
{
	static int h[1024];
	int i, k, m, p, t;

	if (n < 3) {
		a->n = 0;
		return;
	}

	for (p = 0, i = 1; i < n; i++)
		if ((y[i] < y[p]) || (y[i] == y[p] && x[i] < x[p])) p = i;

	for (h[0] = p, m = 1;;) {
		for (k = -1, i = 0; i < n; i++) {
			if (x[i] == x[p] && y[i] == y[p])
				continue;

			if (k < 0) {
				k = i;
				continue;
			}

			t = (x[k] - x[p]) * (y[i] - y[p]) - (x[i] - x[p]) * (y[k] - y[p]);
			if (t > 0)
				continue;

			if (t == 0 && i != h[0]) {
				t = (x[k] - x[p]) * (x[k] - x[p]) +
				    (y[k] - y[p]) * (y[k] - y[p]) +
				    (x[p] - x[i]) * (x[i] - x[p]) +
				    (y[p] - y[i]) * (y[i] - y[p]);

				if (t >= 0)
					continue;
			}

			k = i;
		}

		if (k < 0 || k == h[0])
			break;

		h[m++] = p = k;
	}

	for (a->n = m, h[m] = h[0], i = 0; i <= m; i++) {
		a->x[i] = x[h[i]];
		a->y[i] = y[h[i]];
	}
}

int main()
{
	static int x[256], y[256], nr, nc, no, t;
	static hull_t r, c;
	char *s;
	int i;

	for (t = 1; scanf("%d %d %d", &nc, &nr, &no) == 3; t++) {
		if (nc == 0 && nr == 0 && no == 0)
			break;

		for (i = 0; i < nc; i++)
			scanf("%d %d", &x[i], &y[i]);
		hull(&c, x, y, nc);

		for (i = 0; i < nr; i++)
			scanf("%d %d", &x[i], &y[i]);
		hull(&r, x, y, nr);

		printf("Data set %d:\n", t);
		while (no-- > 0 && scanf("%d %d", &x[0], &y[0]) == 2) {
			if (inside(&c, x[0], y[0]))
				s = "safe";
			else if (inside(&r, x[0], y[0]))
				s = "robbed";
			else
				s = "neither";

			printf("     Citizen at (%d,%d) is %s.\n",
				x[0], y[0], s);
		}
		printf("\n");
	}

	return 0;
}
