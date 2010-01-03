#include <stdio.h>
#include <string.h>

#define NDIG 160

typedef struct {
	int n, d[NDIG];
} num_t;

void set(num_t *z, int a)
{
	memset(z, 0, sizeof(num_t));
	z->d[0] = a;
	z->n = (a == 0) ? 0 : 1;
}

static void muladd(num_t *z, num_t *x, num_t *y)
{
	register int i, j, c;

	if (z->n < (c = x->n + y->n + 4)) {
		for (i = z->n; i < c; i++)
			z->d[i] = 0;
		z->n = c;
	}

	for (i = 0; i < x->n; i++) {
		for (j = 0, c = 0; j < y->n; j++, c /= 10)
			z->d[i+j] = (c += z->d[i+j] + x->d[i] * y->d[j]) % 10;

		for (j += i; c > 0; j++, c /= 10)
			z->d[j] = (c += z->d[j]) % 10;
	}

	while (z->n > 0 && z->d[z->n - 1] == 0)
		z->n--;
}

char *fmt(num_t *x)
{
	static char buf[1024];
	int i, j;

	if (x->n <= 0)
		return "0";

	for (i = x->n - 1; i > 0 && x->d[i] == 0; i--);

	for (j = 0; i >= 0;)
		buf[j++] = x->d[i--] + '0';
	buf[j] = '\0';

	return buf;
}

int main()
{
	static num_t f[512], g[512];
	int i, k, a, t;

	memset(g, 0, sizeof(g));
	for (set(&g[0], 1), set(&g[1], 1), k = 3; k <= 500; k += 2)
		for (i = 0; i < k; i++) muladd(&g[k], &g[i], &g[k - i - 1]);

	memset(f, 0, sizeof(f));
	for (set(&f[0], 1), k = 1; k <= 500; k++)
		for (i = 1; i <= k; i++) muladd(&f[k], &g[i], &f[k - i]);

	for (scanf("%d", &t), k = 1; k <= t && scanf("%d", &a) == 1; k++)
		printf("Case %d: %s\n", k, fmt(&f[a]));

	return 0;
}
