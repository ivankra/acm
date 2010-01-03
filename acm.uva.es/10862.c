#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
	unsigned n, a[1024];
} num_t;

static void set1(num_t *x, unsigned a)
{
	x->n = (a == 0) ? 0 : 1;
	x->a[0] = a;
}

static void copy(num_t *z, num_t *x)
{
	z->n = x->n;
	memcpy(z->a, x->a, x->n * sizeof(unsigned));
}

static void add(num_t *z, num_t *x)
{
	static unsigned m;
	register unsigned i, c;

	if (z->n < x->n) {
		for (i = z->n, m = x->n; i < m; i++)
			z->a[i] = 0;
		z->n = m;
	}

	for (i = 0, c = 0, m = x->n; i < m; i++, c >>= 16)
		z->a[i] = (c += z->a[i] + x->a[i]) & 0xFFFF;

	for (m = z->n; i < m && c != 0; i++, c >>= 16)
		z->a[i] = (c += z->a[i]) & 0xFFFF;

	if (c)
		z->a[z->n++] = c;
}

static void add3(num_t *z, num_t *x, num_t *y)
{
	if (x->n > y->n) {
		copy(z, x);
		add(z, y);
	} else {
		copy(z, y);
		add(z, x);
	}
}

static void add1(num_t *x, unsigned a)
{
	static unsigned m;
	register unsigned i, c;

	if (a == 0)
		return;

	for (i = 0, c = a, m = x->n; i < m && c != 0; i++, c >>= 16)
		x->a[i] = (c += x->a[i]) & 0xFFFF;

	if (c)
		x->a[x->n++] = c;
}

static void mul1(num_t *x, unsigned a)
{
	static unsigned m;
	register unsigned i, c;

	if (a == 0) {
		x->n = 0;
		return;
	}

	for (i = 0, c = 0, m = x->n; i < m; i++, c >>= 16)
		x->a[i] = (c += x->a[i] * a) & 0xFFFF;

	if (c != 0)
		x->a[x->n++] = c;
}

static void mul(num_t *r, num_t *x, num_t *y)
{
	static num_t tmp;
	static unsigned m;
	unsigned i, j, k, c;
	num_t *z;

	z = (r == x || r == y) ? &tmp : r;
	m = y->n;

	for (z->n = c = x->n + y->n + 1, i = 0; i < c; i++)
		z->a[i] = 0;

	for (i = 0; i < x->n; i++) {
		for (c = 0, j = 0, k = i; j < m; j++, k++, c >>= 16)
			z->a[k] = (c += z->a[k] + x->a[i] * y->a[j]) & 0xFFFF;

		for (; c != 0; k++, c >>= 16)
			z->a[k] = (c += z->a[k]) & 0xFFFF;
	}

	while (z->n > 0 && z->a[z->n - 1] == 0)
		z->n--;

	if (r != z)
		copy(r, z);
}

static unsigned div1(num_t *x, unsigned d)
{      
	register unsigned r;
	int i;

	for (i = x->n - 1, r = 0; i >= 0; i--) {
		r = (r << 16) | x->a[i];
		x->a[i] = r / d;
		r %= d;
	}

	while (x->n > 0 && x->a[x->n - 1] == 0)
		x->n--;

	return r;
}

static int cmp(num_t *x, num_t *y)
{
	register int i;

	if (x->n != y->n)
		return ((int)x->n - (int)y->n);

	for (i = x->n - 1; i >= 0; i--)
		if (x->a[i] != y->a[i])
			return ((int)x->a[i] - (int)y->a[i]);

	return 0;
}

static char *fmtx(num_t *x, unsigned b)
{
	static char dig[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	static char res[16][65536], buf[65536];
	static num_t t;
	static int z = 0;
	int i, j;

	if (x->n == 0)
		return "0";

	for (copy(&t, x), i = 0; t.n != 0;)
		buf[i++] = dig[div1(&t, b)];

	for (z = (z + 1) & 15, j = 0; i-- > 0;)
		res[z][j++] = buf[i];
	res[z][j] = '\0';

	return res[z];
}

static char *fmt(num_t *x)
{
	return fmtx(x, 10);
}

static void setx(num_t *x, char *s, unsigned b)
{
	for (set1(x, 0); *s; s++) {
		if ('0' <= *s && *s <= '9') {
			mul1(x, b);
			add1(x, *s - '0');
		} else if ('A' <= *s && *s <= 'Z') {
			mul1(x, b);
			add1(x, *s - 'A' + 10);
		}
	}
}

static void set(num_t *x, char *s)
{
	setx(x, s, 10);
}

int main()
{
	static num_t fib[4096], b;
	int i, n;

	set1(&fib[0], 0);
	set1(&fib[1], 1);

/* f(0)=f(1)=1 f(n) = f(n-1) + 2f(n-2) + 3f(n-3) + ...

  f(n) = Fib(2n);*/

	for (i = 2; i <= 4000; i++)
		add3(&fib[i], &fib[i - 1], &fib[i - 2]);

	while (scanf("%d", &n) == 1 && n > 0)
		printf("%s\n", fmt(&fib[2 * n]));

	return 0;
}
