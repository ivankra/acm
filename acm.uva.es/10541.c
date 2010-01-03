#include <stdio.h>
#include <string.h>

typedef struct {
	unsigned n, a[15];
} num_t;

num_t zero, tab[256][128];
int got[256][128];

void add(num_t *x, num_t *y)
{
	unsigned i, c;
	while (x->n < y->n) x->a[x->n++] = 0;
	for (i = c = 0; i < y->n; i++, c >>= 16)
		x->a[i] = (c += x->a[i] + y->a[i]) & 0xFFFF;
	for (; c > 0 && i < x->n; i++, c >>= 16)
		x->a[i] = (c += x->a[i]) & 0xFFFF;
	if (c) x->a[x->n++] = c;
}

num_t *f(int s, int n)
{
	int i;

	if (s < 0 || n < 0)
		return &zero;

	if (got[s][n])
		return &tab[s][n];

	got[s][n] = 1;

	if (n == 0) {
		if (s == 0) {
			tab[s][n].n = 1;
			tab[s][n].a[0] = 1;
		} else {
			tab[s][n].n = 0;
		}
	} else if (n == 1) {
		tab[s][n].n = 1;
		tab[s][n].a[0] = 1;
	} else {
		for (tab[s][n].n = 0, i = 0; i <= s; i++)
			add(&tab[s][n], f(i, n - 1));
	}

	return &tab[s][n];
}

unsigned div1(num_t *x, unsigned d)
{
	unsigned i, r;
	for (r = 0, i = x->n; i--;) {
		r = (r << 16) | x->a[i];
		x->a[i] = r / d;
		r %= d;
	}
	while (x->n > 0 && x->a[x->n - 1] == 0) x->n--;
	return (unsigned)r;
}

int main()
{
	num_t z;
	int a[256], i, n, k, s, t;

	zero.n = 0;
	memset(got, 0, sizeof(got));

	for (scanf("%d", &t); t-- > 0 && scanf("%d %d", &n, &k) == 2;) {
		for (i = s = 0; i < k && scanf("%d", &a[i]) == 1; i++)
			s += a[i];

		if (k >= 2)
			s += k - 1;

		memcpy(&z, f(n - s, k + 1), sizeof(num_t));
		for (i = 0; z.n > 0 || i == 0; i++)
			a[i] = div1(&z, 10) + '0';
		while (i-- > 0)
			putchar(a[i]);
		printf("\n");
	}

	return 0;
}
