#include <stdio.h>

#define SQ(x) ((x) * (x))

struct kingdom {
	int sx[128], sy[128], sn;
	int h[128], x[128], y[128], n, area2, got;
};

int hull(int h[], int x[], int y[], int n)
{
	int i, j, k, p, t;

	for (k = 0, i = 1; i < n; i++)
		if (y[i] < y[k] || (y[i] == y[k] && x[i] > x[k])) k = i;

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
	return k;
}

int inside(int x[], int y[], int n, int x0, int y0)
{
	int i, t;

	for (i = 0; i < n; i++) {
		t = (x[i] - x0) * (y[i + 1] - y0) - (x[i + 1] - x0) * (y[i] - y0);
		if (t <= 0) return 0;
	}

	return 1;
}

int readk(struct kingdom *k)
{
	int i, j;

	if (scanf("%d", &k->sn) != 1 || k->sn <= 0)
		return 0;

	for (i = 0; i < k->sn; i++)
		scanf("%d %d", &k->sx[i], &k->sy[i]);

	k->n = hull(k->h, k->sx, k->sy, k->sn);
	for (i = 0; i <= k->n; i++) {
		k->x[i] = k->sx[k->h[i]];
		k->y[i] = k->sy[k->h[i]];
	}

	for (j = 0, i = 0; i < k->n; i++)
		j += k->x[i] * k->y[i + 1] - k->x[i + 1] * k->y[i];

	k->area2 = j;
	k->got = 0;
	return 1;
}

int main()
{
	static struct kingdom k[32];
	int i, n, x, y;

	for (n = 0; readk(&k[n]); n++);

	while (scanf("%d %d", &x, &y) == 2) {
		for (i = 0; i < n; i++) {
			if (inside(k[i].x, k[i].y, k[i].n, x, y)) {
				k[i].got++;
				break;
			}
		}
	}

	for (y = 0, i = 0; i < n; i++)
		if (k[i].got) y += k[i].area2;

	printf("%d.%s\n", y >> 1, (y & 1) ? "50" : "00");
	return 0;
}
