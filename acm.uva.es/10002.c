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

	h[k] = h[0];
	return k;
}

void print(long long p, long long q)
{
	long long t;

	if (q < 0) {
		q = -q;
		p = -p;
	}

	if (p < 0) {
		p = -p;
		putchar('-');
	}

	p *= 1000LL;
	t = p / q;

	if ((2LL * (p % q)) >= q)
		t++;

	printf("%lld.", (long long)(t / 1000LL));
	printf("%.3d", (int)(t % 1000LL));
}

int main()
{
	static int sx[128], sy[128], x[128], y[128], h[128], n;
	int i;
	long long a, d, cx, cy;

	while (scanf("%d", &n) == 1 && n >= 3) {
		for (i = 0; i < n; i++)
			scanf("%d %d", &sx[i], &sy[i]);

		n = hull(h, sx, sy, n);

		for (i = 0; i <= n; i++) {
			x[i] = sx[h[i]];
			y[i] = sy[h[i]];
		}

		cx = 0;
		cy = 0;

		for (i = 1, d = 0; i < (n - 1); i++) {
			a = (long long)(x[i] - x[0]) * (long long)(y[i + 1] - y[0])
				- (long long)(x[i + 1] - x[0]) * (long long)(y[i] - y[0]);
			if (a < 0) a = -a;

			d += a;

			cx += a * (long long)(x[0] + x[i] + x[i + 1]);
			cy += a * (long long)(y[0] + y[i] + y[i + 1]);
		}

		d *= 3;

		print(cx, d);
		printf(" ");
		print(cy, d);
		printf("\n");
	}

	return 0;
}
