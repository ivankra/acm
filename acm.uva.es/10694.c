#include <stdio.h>
#include <string.h>

typedef struct {
	unsigned n, a[63];
} num_t;

void set(num_t *z, unsigned x)
{
	z->n = x ? 1 : 0;
	z->a[0] = x;
}

void inc(num_t *z)
{
	unsigned i;
	for (i = 0; i < z->n; i++) {
		z->a[i]++;
		if (z->a[i] & 0x80000000)
			z->a[i] = 0;
		else
			return;
	}
	z->a[z->n++] = 1;
}

void add2(num_t *z, num_t *x)
{
	unsigned i, c;

	while (z->n < x->n)
		z->a[z->n++] = 0;

	for (i = c = 0; i < x->n; i++, c >>= 31)
		z->a[i] = (c += z->a[i] + x->a[i]) & 0x7FFFFFFF;

	for (; c && i < z->n; c >>= 1)
		z->a[i] = (c += z->a[i]) & 0x7FFFFFFF;

	if (c) z->a[z->n++] = c;
}

void add3(num_t *z, num_t *x, num_t *y)
{
	unsigned i, c;

	if (x->n < y->n) {
		z->n = y->n;

		for (i = c = 0; i < x->n; i++, c >>= 31)
			z->a[i] = (c += x->a[i] + y->a[i]) & 0x7FFFFFFF;

		for (; i < y->n; i++, c >>= 31)
			z->a[i] = (c += y->a[i]) & 0x7FFFFFFF;
	} else {
		z->n = x->n;

		for (i = c = 0; i < y->n; i++, c >>= 31)
			z->a[i] = (c += x->a[i] + y->a[i]) & 0x7FFFFFFF;

		for (; i < x->n; i++, c >>= 31)
			z->a[i] = (c += x->a[i]) & 0x7FFFFFFF;
	}

	if (c) z->a[z->n++] = c;
}

char *fmt(char *s, num_t *z)
{
	static char t[1024];
	unsigned i, j;
	unsigned long long r;

	for (i = 0; z->n > 0;) {
		for (r = 0, j = z->n; j--;) {
			r = (r << 31) | (unsigned long long)z->a[j];
			z->a[j] = r / 10ULL;
			r %= 10ULL;
		}

		t[i++] = (unsigned)r + '0';

		while (z->n > 0 && z->a[z->n - 1] == 0)
			z->n--;
	}

	while (i-- > 0)
		*s++ = t[i];
	*s++ = '\0';

	return s;
}

num_t tab[2048];

void make()
{
	static num_t t1, t2;
	num_t *a, *b;
	int i;

	a = &t1;
	b = &t2;

	set(a, 0);
	set(b, 0);
	set(&tab[0], 0);

	for (i = 1; i <= 2000; i++) {
		add2(b, a);
		inc(b);
		a = b;
		b = (b == &t1) ? &t2 : &t1;
		add3(&tab[i], &tab[i - 1], a);
	}
}

int main()
{
	static char buf[1048576], *s[2048];
	char *p = buf;
	int n, t;

	make();

	memset(s, 0, sizeof(s));
	for (scanf("%d", &t); t-- > 0 && scanf("%d", &n) == 1;) {
		if (n <= 0) {
			printf("0\n");
		} else {
			if (s[n] == NULL)
				p = fmt(s[n] = p, &tab[n]);
			printf("%s\n", s[n]);
		}
	}

	return 0;
}
