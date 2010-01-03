#include <stdio.h>

#define RADIX 1000000

typedef struct {
	int n;
	int a[383];
} num_t;

static void set(num_t *x, int a)
{
	x->n = 1;
	x->a[0] = a;
}

static void mul(num_t *z, int k, num_t *x)
{
	register int i, c;

	for (i = 0, c = 0; i < x->n; i++, c /= RADIX)
		z->a[i] = (c += x->a[i] * k) % RADIX;

	for (z->n = x->n; c != 0; c /= RADIX)
		z->a[z->n++] = c % RADIX;
}

static void inc(num_t *x)
{
	register int i;

	for (i = 0; i < x->n; i++) {
		if (++(x->a[i]) < RADIX) return;
		x->a[i] = 0;
	}

	x->a[x->n++] = 1;
}

static void dec(num_t *x)
{
	register int i;

	for (i = 0;; i++) {
		if (x->a[i]-- > 0) return;
		x->a[i] = RADIX - 1;
	}
}

static void print(num_t *x)
{
	int i;

	printf("%d", x->a[x->n - 1]);
	for (i = x->n - 2; i >= 0; i--)
		printf("%.6d", x->a[i]);
	putchar('\n');
}


int main()
{
	static num_t tab[801];
	int n, k;

	for (set(&tab[0], 1), set(&tab[1], 0), k = 2; k <= 800; k++) {
		mul(&tab[k], k, &tab[k - 1]);

		if (k & 1)
			dec(&tab[k]);
		else
			inc(&tab[k]);
	}

	while (scanf("%d", &n) == 1 && n >= 0)
		print(&tab[n]);

	return 0;
}
