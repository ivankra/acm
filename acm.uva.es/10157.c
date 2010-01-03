#include <stdio.h>
#include <string.h>

#define NLIMBS 24

typedef struct {
	unsigned a[NLIMBS], n;
} num_t;

void set(num_t *x, unsigned a)
{
	x->n = (x->a[0] = a) ? 1 : 0;
}

void copy(num_t *z, num_t *x)
{
	memcpy(z->a, x->a, (z->n = x->n) * sizeof(x->a[0]));
}

void muladd(num_t *z, num_t *x, num_t *y)
{
	unsigned i, j, k, c;

	for (k = x->n + y->n + 1; z->n < k;)
		z->a[z->n++] = 0;
	z->a[z->n++] = 0;

	for (i = 0; i < x->n; i++) {
		for (c = j = 0, k = i; j < y->n; j++, k++, c >>= 16)
			z->a[k] = (c += z->a[k] + x->a[i] * y->a[j]) & 0xFFFF;

		for (; c > 0; k++, c >>= 16)
			z->a[k] = (c += z->a[k]) & 0xFFFF;
	}

	while (z->n > 0 && z->a[z->n - 1] == 0)
		z->n--;
}

void sub(num_t *z, num_t *x)
{
	unsigned i, b;

	for (b = 0, i = 0; i < z->n; i++) {
		if (z->a[i] >= (x->a[i] + b)) {
			z->a[i] -= x->a[i] + b;
			b = 0;
		} else {
			z->a[i] = 0x10000 + z->a[i] - x->a[i] - b;
			b = 1;
		}
	}

	while (z->n > 0 && z->a[z->n - 1] == 0)
		z->n--;
}

void print(num_t *t)
{
	static unsigned s[65536];
	unsigned i, k, r;

	for (k = 0; k == 0 || t->n > 0;) {
		for (r = 0, i = t->n; i-- > 0; r %= 10)
			t->a[i] = (r = (r << 16) | t->a[i]) / 10;

		for (s[k++] = r; t->n > 0 && t->a[t->n - 1] == 0; t->n--);
	}

	while (k-- > 0)
		putchar(s[k] + '0');
	putchar('\n');
}

num_t zero, one, tab[160][160];
int got[160][160];

num_t *f(int n, int d)
{
	int k;

	if (n < 0 || d < 0 || (n & 1) != 0)
		return &zero;

	if (n == 0)
		return &one;

	if (got[n >> 1][d])
		return &tab[n >> 1][d];

	for (set(&tab[n >> 1][d], 0), k = 2; k <= n; k += 2)
		muladd(&tab[n >> 1][d], f(k - 2, d - 1), f(n - k, d));

	got[n >> 1][d] = 1;
	return &tab[n >> 1][d];
}

int main()
{
	static num_t t;
	int n, d;

	set(&zero, 0);
	set(&one, 1);
	memset(got, 0, sizeof(got));

	while (scanf("%d %d", &n, &d) == 2) {
		copy(&t, f(n, d));
		sub(&t, f(n, d - 1));
		print(&t);
	}

	return 0;
}
