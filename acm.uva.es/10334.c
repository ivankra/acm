#include <stdio.h>

typedef struct {
	int n;
	int d[1024];
} num_t;

void add(num_t *z, num_t *x, num_t *y)
{
	int i, m, c;

	m = (x->n < y->n) ? x->n : y->n;

	for (i = 0, c = 0; i < m; i++, c /= 10)
		z->d[i] = (c += x->d[i] + y->d[i]) % 10;

	if (x->n == m)
		x = y;

	for (; i < x->n; i++, c /= 10)
		z->d[i] = (c += x->d[i]) % 10;

	if (c)
		z->d[i++] = c;

	z->n = i;
}

void set(num_t *z, int d)
{
	z->n = 1;
	z->d[0] = d;
}

int main()
{
	static num_t a[1024];
	int i, n;

	set(&a[0], 1);
	set(&a[1], 2);
	for (i = 2; i <= 1000; i++)
		add(&a[i], &a[i - 1], &a[i - 2]);

	while (scanf("%d", &n) == 1) {
		for (i = a[n].n - 1; i >= 0; i--)
			putchar(a[n].d[i] + '0');
		putchar('\n');
	}

	return 0;
}
