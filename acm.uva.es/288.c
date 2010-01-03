#include <stdio.h>
#include <string.h>

typedef struct {
	int sign, n;
	unsigned a[8192];
} num_t;

char *tokptr;
int token, isdig[256];
num_t toknum;

static char *fmt(num_t *x);

static void set1(num_t *x, int a)
{
	x->sign = (a >= 0) ? 1 : -1;
	x->n = (a != 0) ? 1 : 0;
	x->a[0] = (a >= 0) ? a : (-a);
}

static void copy(num_t *z, num_t *x)
{
	if (z != x) {
		z->n = x->n;
		z->sign = x->sign;
		memcpy(z->a, x->a, x->n * sizeof(x->a[0]));
	}
}

static void neg(num_t *x)
{
	if (x->n != 0)
		x->sign *= -1;
}

static int abscmp(num_t *x, num_t *y)
{
	int i;

	if (x->n != y->n)
		return (x->n - y->n);

	for (i = x->n - 1; i >= 0; i--)
		if (x->a[i] != y->a[i])
			return ((int)x->a[i] - (int)y->a[i]);

	return 0;
}

#if 0
static int cmp(num_t *x, num_t *y)
{
	if (x->sign != y->sign)
		return (x->sign - y->sign);
	else
		return (x->sign * abscmp(x, y));
}
#endif

static void absadd1(num_t *x, unsigned c)
{
	int i;

	for (i = 0; i < x->n && c != 0; i++, c >>= 16)
		x->a[i] = (c += x->a[i]) & 0xFFFF;

	if (c != 0)
		x->a[x->n++] = c;
}

static void absadd(num_t *z, num_t *x, num_t *y)
{
	int i, m;
	unsigned c;

	m = (x->n < y->n) ? x->n : y->n;

	for (i = 0, c = 0; i < m; i++, c >>= 16)
		z->a[i] = (c += x->a[i] + y->a[i]) & 0xFFFF;

	for (; i < x->n; i++, c >>= 16)
		z->a[i] = (c += x->a[i]) & 0xFFFF;

	for (; i < y->n; i++, c >>= 16)
		z->a[i] = (c += y->a[i]) & 0xFFFF;

	if (c)
		z->a[i++] = c;

	z->n = i;
	z->sign = 1;
}

static void abssub(num_t *z, num_t *x, num_t *y)
{
	int i;
	unsigned c;

	if (abscmp(x, y) < 0) {
		abssub(z, y, x);
		if (z->n != 0)
			z->sign *= -1;

		return;
	}

	if (y->n == 0) {
		if (z != x) {
			copy(z, x);
			z->sign = 1;
		}
		return;
	}

	/* x >= y */

	for (i = 0, c = 1; i < y->n; i++, c >>= 16)
		z->a[i] = (c += x->a[i] + (y->a[i] ^ 0xFFFF)) & 0xFFFF;

	for (; i < x->n; i++, c >>= 16)
		z->a[i] = (c += x->a[i] + 0xFFFF) & 0xFFFF;

	while (i > 0 && z->a[i - 1] == 0)
		i--;

	z->n = i;
	z->sign = 1;
}

static void add(num_t *z, num_t *x, num_t *y)
{
	if (x->sign == y->sign) {
		int s = x->sign;
		absadd(z, x, y);
		z->sign = (z->n == 0) ? 1 : s;
	} else if (x->sign > y->sign) {
		abssub(z, x, y);
	} else {
		abssub(z, y, x);
	}
}

static void mul1(num_t *x, unsigned a)
{
	int i;
	unsigned c;

	if (a == 1)
		return;

	for (i = 0, c = 0; i < x->n; i++, c >>= 16)
		x->a[i] = (c += a * x->a[i]) & 0xFFFF;

	if (c != 0)
		x->a[x->n++] = c;
}

static unsigned div1(num_t *x, unsigned d)
{
	unsigned r;
	int i;

	for (i = x->n - 1, r = 0; i >= 0; i--) {
		r = (r << 16) | x->a[i];
		x->a[i] = r / d;
		r %= d;
	}

	while (x->n > 0 && x->a[x->n - 1] == 0)
		x->n--;

	if (x->n == 0)
		x->sign = 1;

	return r;
}

static char *fmt(num_t *x)
{
	static char buf[16][65536];
	static int r[65536], z;
	static num_t t;
	char *s;
	int i, k;

	if (x->n == 0)
		return "0";

	for (i = 0, copy(&t, x); t.n != 0;)
		r[i++] = div1(&t, 10000);

	s = buf[z = (z + 1) & 15];

	if (x->sign < 0)
		*s++ = '-';

	s += sprintf(s, "%d", r[--i]);
	while (i-- > 0) {
		k = r[i];
		*s++ = (k / 1000) + '0';
		k %= 1000;
		*s++ = (k / 100) + '0';
		k %= 100;
		*s++ = (k / 10) + '0';
		*s++ = (k % 10) + '0';
	}
	*s = '\0';

	return buf[z];
}

static void mul(num_t *r, num_t *x, num_t *y)
{
	static num_t t;
	int i, j, k;
	unsigned c;
	num_t *z;

	z = (r == x || r == y) ? &t : r;
	z->sign = x->sign * y->sign;

	for (z->n = k = x->n + y->n + 1, i = 0; i < k; i++)
		z->a[i] = 0;

	for (i = 0; i < x->n; i++) {
		for (j = 0, k = i, c = 0; j < y->n; j++, k++, c >>= 16)
			z->a[k] = (c += z->a[k] + x->a[i] * y->a[j]) & 0xFFFF;

		for (; c != 0; k++, c >>= 16)
			z->a[k] = (c += z->a[k]) & 0xFFFF;
	}

	while (z->n > 0 && z->a[z->n - 1] == 0)
		z->n--;

	if (z->n == 0)
		z->sign = 1;

	if (z != r)
		copy(r, z);
}

static void set(num_t *x, char *p)
{
	int a, m, s;

	set1(x, 0);
	for (set1(x, 0), a = 0, m = 1; isdig[*p];) {
		a = a * 10 + *p++ - '0';
		if ((m *= 10) == 10000) {
			mul1(x, m);
			absadd1(x, a);
			a = 0;
			m = 1;
		}
	}

	if (m != 1) {
		mul1(x, m);
		absadd1(x, a);
	}
}

static void expon(num_t *z, num_t *x, num_t *y)
{
	static num_t t;
	num_t *a;
	int k;

	if (x == z) {
		copy(&t, x);
		a = &t;
	} else {
		a = x;
	}

	for (k = y->n * 16 - 1; k >= 0; k--)
		if ((y->a[k >> 4] >> (k & 15)) & 1) break;

	for (set1(z, 1); k >= 0; k--) {
		mul(z, z, z);

		if ((y->a[k >> 4] >> (k & 15)) & 1)
			mul(z, z, a);
	}
}

static int next()
{
	for (;;) {
		if (*tokptr == '\0')
			return (token = -1);

		if (isdig[(unsigned)*tokptr]) {
			set(&toknum, tokptr);

			while (isdig[(unsigned)*tokptr])
				tokptr++;

			return (token = 'n');
		}

		if (*tokptr == '+' || *tokptr == '-' || *tokptr == '^')
			return (token = *tokptr++);

		if (*tokptr == '*') {
			tokptr++;

			if (*tokptr != '*')
				return (token = '*');

			tokptr++;
			return (token = '^');
		}

		tokptr++;
	}
}

static void powr(num_t *z)
{
	if (token != 'n') {
		fprintf(stderr, "powr: expected an integer\n");
		set1(z, 0);
		return;
	}

	copy(z, &toknum);

	if (next() == '^') {
		num_t x;
		next();
		powr(&x);
		expon(z, z, &x);
	}
}

static void term(num_t *z)
{
	static num_t x;

	for (powr(z); token == '*';) {
		next();
		powr(&x);
		mul(z, z, &x);
	}
}

static void eval(num_t *z)
{
	static num_t x;

	for (term(z);;) {
		if (token == '+') {
			next();
			term(&x);
			add(z, z, &x);
		} else if (token == '-') {
			next();
			term(&x);
			neg(&x);
			add(z, z, &x);
		} else {
			return;
		}
	}
}

int main()
{
	static char line[1048576];
	static num_t z;
	int i;

	for (i = 0; i < 256; i++)
		isdig[i] = ('0' <= i && i <= '9');

	while (gets(line)) {
		tokptr = line;
		next();

		eval(&z);

		printf("%s\n", fmt(&z));
	}

	return 0;
}
