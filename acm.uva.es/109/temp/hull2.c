#include <stdio.h>

#define SQ(x) ((x) * (x))

int main()
{
	int x[128], y[128], hu[128], hx[128], hy[128], n;
	int i, j, k, t;

	scanf("%d", &n);

	for (i = 0; i < n; i++)
		scanf("%d %d", &x[i], &y[i]);

	for (k = 0, i = 1; i < n; i++)
		if (y[i] < y[k] || (y[i] == y[k] && x[i] > x[k])) k = i;

	hu[0] = k;
	hx[0] = x[k];
	hy[0] = y[k];

	for (k = 1;; k++) {
		for (j = -1, i = 0; i < n; i++) {
			if (x[i] == hx[k - 1] && y[i] == hy[k - 1])
				continue;

			if (j < 0) {
				j = i;
				continue;
			}

			t = (x[j] - hx[k - 1]) * (y[i] - hy[k - 1])
				- (x[i] - hx[k - 1]) * (y[j] - hy[k - 1]);

			if (t > 0)
				continue;

			if (t == 0 && i != hu[0]) {
				if ((SQ(x[i] - hx[k - 1]) + SQ(y[i] - hy[k - 1])) <=
				    (SQ(x[j] - hx[k - 1]) + SQ(y[j] - hy[k - 1])))
					continue;
			}

			j = i;
		}

		if (j < 0 || j == hu[0])
			break;

		hu[k] = j;
		hx[k] = x[j];
		hy[k] = y[j];
	}

	hu[k] = hu[0];
	hx[k] = hx[0];
	hy[k] = hy[0];
	k++;

	for (i = 0; i < k; i++)
		printf("%d %d\n", hx[i], hy[i]);

	return 0;
}
