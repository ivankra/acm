#include <stdio.h>

#define SQ(x) ((x) * (x))

int main()
{
	int x[128], y[128], h[128], n;
	int i, j, k, t;

	scanf("%d", &n);

	for (i = 0; i < n; i++)
		scanf("%d %d", &x[i], &y[i]);

	for (k = 0, i = 1; i < n; i++)
		if (y[i] < y[k] || (y[i] == y[k] && x[i] > x[k])) k = i;

	h[0] = k;
	for (k = 1;; k++) {
		for (j = -1, i = 0; i < n; i++) {
			if (x[i] == x[h[k - 1]] && y[i] == y[h[k - 1]])
				continue;

			if (j < 0) {
				j = i;
				continue;
			}

			t = (x[j] - x[h[k - 1]]) * (y[i] - y[h[k - 1]])
				- (x[i] - x[h[k - 1]]) * (y[j] - y[h[k - 1]]);

			if (t > 0)
				continue;

			if (t == 0 && i != h[0]) {
				if ((SQ(x[i] - x[h[k - 1]]) + SQ(y[i] - y[h[k - 1]])) <=
				    (SQ(x[j] - x[h[k - 1]]) + SQ(y[j] - y[h[k - 1]])))
					continue;
			}

			j = i;
		}

		if (j < 0 || j == h[0])
			break;

		h[k] = j;
	}
	h[k++] = h[0];

	for (i = 0; i < k; i++)
		printf("%d %d\n", x[h[i]], y[h[i]]);

	return 0;
}
