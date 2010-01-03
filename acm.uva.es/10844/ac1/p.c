#include <stdio.h>
#include <string.h>

typedef struct {
	int n;
	unsigned a[192];
} num_t;

static char *fmt(num_t *x)
{
	static char s1[16384], s2[16384];
	static num_t t;
	int i, k;
	unsigned long long c;

	memcpy(&t, x, sizeof(num_t));

	for (k = 0;;) {
		for (i = t.n - 1, c = 0; i >= 0; i--) {
			c = (c << 32) | (unsigned long long)t.a[i];
			t.a[i] = c / 1000000000ULL;
			c %= 1000000000ULL;
		}

		for (i = 0; i < 9; i++, c /= 10ULL)
			s1[k++] = '0' + (int)(c % 10ULL);

		while (t.n > 0 && t.a[t.n - 1] == 0) t.n--;
		if (t.n <= 0) break;
	}

	for (k--; k > 0 && s1[k] == '0'; k--);

	for (i = 0; k >= 0;)
		s2[i++] = s1[k--];
	s2[i] = '\0';

	return s2;
}

static void set(num_t *x, unsigned c)
{
	x->n = (c == 0) ? 0 : 1;
	x->a[0] = c;
}

static void add(num_t *x, num_t *y)
{
	register int i;
	unsigned long long c;

	while (x->n < y->n)
		x->a[x->n++] = 0;

	for (i = 0, c = 0; i < y->n; i++, c >>= 32)
		x->a[i] = (unsigned)(c += (unsigned long long)x->a[i] + (unsigned long long)y->a[i]);

	for (; i < x->n && c; i++, c >>= 32)
		x->a[i] = (unsigned)(c += (unsigned long long)x->a[i]);

	if (c)
		x->a[x->n++] = c;

	while (x->n > 0 && x->a[x->n - 1] == 0)
		x->n--;
}

static void add4(num_t *z, num_t *x, unsigned k, num_t *y)
{
	static int m;
	register int i;
	register unsigned long long c;

	for (c = z->n = x->n + y->n, i = 0; i < c; i++)
		z->a[i] = 0;

	m = (x->n < y->n) ? x->n : y->n;
	for (i = 0, c = 0; i < m; i++, c >>= 32)
		z->a[i] = (unsigned)(c += (unsigned long long)x->a[i] + (unsigned long long)k * (unsigned long long)y->a[i]);

	for (; i < x->n; i++, c >>= 32)
		z->a[i] = (unsigned)(c += (unsigned long long)x->a[i]);

	for (; i < y->n; i++, c >>= 32)
		z->a[i] = (unsigned)(c += (unsigned long long)k * (unsigned long long)y->a[i]);

	for (; i < z->n && c; i++, c >>= 32)
		z->a[i] = (unsigned)(c += (unsigned long long)z->a[i]);

	if (c)
		z->a[z->n++] = c;

	while (z->n > 0 && z->a[z->n - 1] == 0)
		z->n--;
}

static num_t res[1024];

static void mktab()
{
	static num_t tab1[1024], tab2[1024];
	num_t *tab, *next;
	int n, i;

	tab = tab1;
	next = tab2;

	for (n = 0;;) {
		set(&res[n], 0);
		for (i = 1; i <= n; i++)
			add(&res[n], &tab[i]);

		if (++n > 901)
			break;

		set(&next[1], 1);
		set(&next[n], 1);
		for (i = 2; i < n; i++)
			add4(&next[i], &tab[i - 1], i, &tab[i]);

		tab = next;
		next = (next == tab1) ? tab2 : tab1;
	}
}

int main()
{
	int n;

	mktab();

	while (scanf("%d", &n) == 1 && n >= 1)
		printf("%d, %s\n", n, fmt(&res[n]));

	return 0;
}
