#include <stdio.h>

int main()
{
	static int x[8192], y[8192], z[8192], d[8192], r[16], n;
	register int i, j, k, m;

	for (n = 0; scanf("%d%d%d", &x[n], &y[n], &z[n]) == 3 &&
		     (x[n] | y[n] | z[n]) != 0; n++);

	for (i = 0; i < n; i++) {
		for (j = 0, m = 0xFFFFFF; j < n; j++) {
			if (i == j) continue;

#define S(x) ((x) * (x))
			k = S(x[i] - x[j]) + S(y[i] - y[j]) + S(z[i] - z[j]);
			if (k < m)
				m = k;
#undef S
		}

		d[i] = m;
	}

	for (i = 0; i < 16; i++)
		r[i] = 0;

	for (i = 0; i < n; i++) {
		for (j = 1; j < 11; j++)
			if (d[i] < (j * j)) break;
		r[j]++;
	}

	for (i = 1; i <= 10; i++)
		printf("%4d", r[i]);
	printf("\n");

	return 0;
}
