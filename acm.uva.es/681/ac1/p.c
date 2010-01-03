#include <stdio.h>

#define SQ(x) ((x) * (x))

int hull(int h[], int x[], int y[], int n)
{
	int i, j, k, p, t;

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

	h[k++] = h[0];

	return k;
}

int main()
{
	int x[1024], y[1024], h[1024];
	int i, n, t;

	scanf("%d", &t);
	printf("%d\n", t);

	while (t-- > 0 && scanf("%d", &n) == 1) {
		for (i = 0; i < n; i++)
			scanf("%d %d", &x[i], &y[i]);
		scanf("%*d");

		n = hull(h, x, y, n);
		printf("%d\n", n);
		for (i = 0; i < n; i++)
			printf("%d %d\n", x[h[i]], y[h[i]]);

		if (t > 0) printf("-1\n");
	}

	return 0;
}
