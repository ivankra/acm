#include <stdio.h>

int a[1024], n;

void solve(double *r1, double *r2)
{
	int i, up = 0, down = 0, n_up = 0, n_up_s = 0, n_down = 0, n_down_s = 0;

	for (i = 1; i < n && a[i - 1] == a[i]; i++);
	if (i >= n) return;

	if (a[i] > a[i - 1]) {
		up = 1;
		n_up = i - 1;
		n_up_s = 1;
	} else {
		down = 1;
		n_down = i - 1;
		n_down_s = 1;
	}

	for (; i < n; i++) {
		if (up && a[i] >= a[i - 1]) {
			n_up++;
		} else if (down && a[i] <= a[i - 1]) {
			n_down++;
		} else if (up && a[i] < a[i - 1]) {
			up = 0;
			down = 1;
			n_down++;
			n_down_s++;
		} else if (down && a[i] > a[i - 1]) {
			down = 0;
			up = 1;
			n_up++;
			n_up_s++;
		}
	}

	*r1 = n_up_s ? ((double)n_up / (double)n_up_s) : 0.;
	*r2 = n_down_s ? ((double)n_down / (double)n_down_s) : 0.;
}

int main()
{
	double x, y;

	for (;;) {
		for (n = 0; scanf("%d", &a[n]) == 1 && a[n] != 0; n++);
		if (n == 0) break;
		x = y = 0;
		solve(&x, &y);
		printf("Nr values = %d:  %.6f %.6f\n", n, x, y);
	}

	return 0;
}
