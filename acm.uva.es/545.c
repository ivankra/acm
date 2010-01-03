#include <stdio.h>
#include <string.h>

#define PREC 4096

int a[PREC], n;
int rd[10000], re[10000];

void halve()
{
	int i, j, r;

	for (i = r = 0; i < PREC && (r * 10 + a[i]) <= 1; i++, n++)
		r = (r * 10 + a[i]) & 1;

	for (j = 0; i < PREC; r &= 1)
		a[j++] = (r = r * 10 + a[i++]) >> 1;

	if (j < PREC) {
		a[j++] = 5 * r;
		while (j < PREC)
			a[j++] = 0;
	}
}

int main()
{
	int i, j, k, t;

	memset(a, 0, sizeof(a));
	a[0] = 1;
	n = 0;

	for (i = 0; i <= 10000; i++, halve()) {
		for (j = k = 0; j < 5; j++)
			k = k * 10 + a[j];
		rd[i] = (k + 5) / 10;
		re[i] = n;
	}

	for (scanf("%d", &t); t-- > 0 && scanf("%d", &n) == 1;)
		printf("2^-%d = %d.%.3dE-%d\n", n, rd[n] / 1000, rd[n] % 1000, re[n]);

	return 0;
}
