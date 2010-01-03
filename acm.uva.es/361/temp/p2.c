#include <stdio.h>

#define SQ(x) ((x)*(x))

typedef struct {
	int x[256], y[256], n;
} hull_t;

void hull(hull_t *a, int x[], int y[], int n)
{
	static int h[1024];
	int i, j, k, p, t;

	if (n < 3) {
		a->n = 0;
		return;
	}

	for (k = 0, i = 1; i < n; i++)
		if (y[i] < y[k] || (y[i] == y[k] && x[i] < x[k])) k = i;

	h[0] = p = k;
	for (k = 1;; k++) {
		for (j = -1, i = 0; i < n; i++) {
			if (x[i] == x[p] && y[i] == y[p])
				continue;

			if (j < 0) {
				j = i;
				continue;
			}

			t = (x[j] - x[p]) * (y[i] - y[p])
				- (x[i] - x[p]) * (y[j] - y[p]);

			if (t > 0)
				continue;

			if (t == 0 && i != h[0]) {
				if ((SQ(x[i] - x[p]) + SQ(y[i] - y[p])) <=
				    (SQ(x[j] - x[p]) + SQ(y[j] - y[p])))
					continue;
			}

			j = i;
		}

		if (j < 0 || j == h[0])
			break;

		h[k] = p = j;
	}

	h[k] = h[0];
	for (a->n = k, i = 0; i <= k; i++) {
		a->x[i] = x[h[i]];
		a->y[i] = y[h[i]];
	}
}

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

int main()
{
	static int x[1024], y[1024], nr, nc, no, t;
	static hull_t r, c;
	char *s;
	int i;

	for (t = 1; scanf("%d %d %d", &nc, &nr, &no) == 3; t++) {
		if (nc == 0 && nr == 0 && no == 0)
			break;

		for (i = 0; i < nc && scanf("%d %d", &x[i], &y[i]) == 2; i++);
		hull(&c, x, y, nc);

		for (i = 0; i < nr && scanf("%d %d", &x[i], &y[i]) == 2; i++);
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
