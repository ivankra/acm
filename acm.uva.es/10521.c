#include <stdio.h>
#include <assert.h>

typedef struct {
	unsigned n, a[512];
	int sign;
} num_t;

void set1(num_t *x, int c)
{
	x->sign = (c < 0) ? -1 : 1;
	x->a[0] = c * x->sign;
	x->n = (c != 0) ? 1 : 0;
}

void muladd1(num_t *x, unsigned m, unsigned c)
{
	unsigned i;

	for (i = 0; i < x->n; i++, c >>= 16)
		x->a[i] = (c += m * x->a[i]) & 0xFFFF;

	if (c) x->a[x->n++] = c;
}

void uinc(num_t *x)
{
	unsigned i;
	for (i = 0; i < x->n; i++)
		if (++x->a[i] < 0x10000) return; else x->a[i] = 0;
	x->a[x->n++] = 1;
}

void usub(num_t *z, num_t *x, num_t *y)
{
	unsigned i, c;

	assert(x->n >= y->n);

	for (i = 0, c = 0; i < y->n; i++) {
		c += y->a[i];
		if (x->a[i] >= c) {
			z->a[i] = x->a[i] - c;
			c = 0;
		} else {
			z->a[i] = x->a[i] + 0x10000 - c;
			c = 1;
		}
	}

	if (c) {
		for (; i < x->n; i++) {
			z->a[i] = x->a[i] - 1;
			if (x->a[i] > 0) break; else z->a[i] = 0;
		}
		assert(i < x->n);
	}

	for (; i < x->n; i++)
		z->a[i] = x->a[i];

	z->n = x->n;
	while (z->n > 0 && z->a[z->n - 1] == 0) z->n--;
}

void cvt(num_t *x, char *s)
{
	unsigned m, a;

	set1(x, 0);

	for (m = 1, a = 0; *s; s++) {
		if ('0' <= *s && *s <= '9') {
			m *= 10;
			a = a * 10 + *s - '0';

			if (m == 10000) {
				muladd1(x, m, a);
				m = 1;
				a = 0;
			}
		} else if (*s == '-') {
			x->sign *= -1;
		}
	}

	muladd1(x, m, a);

	while (x->n > 0 && x->a[x->n - 1] == 0) x->n--;
	if (x->n == 0) x->sign = 1;
}

void lshift(num_t *x, unsigned s)
{
	unsigned i, c;

	for (i = 0, c = 0; i < x->n; i++, c >>= 16)
		x->a[i] = (c |= x->a[i] << s) & 0xFFFF;

	if (c != 0)
		x->a[x->n++] = c;
}

void rshift(num_t *x, unsigned s)
{
	unsigned i, c;
	for (i = x->n, c = 0; i--; c <<= 16)
		x->a[i] = ((c |= x->a[i]) >> s) & 0xFFFF;
}

unsigned udiv1(num_t *q, num_t *x, unsigned y)
{
	unsigned i, r;

	for (i = x->n, r = 0; i--;) {
		r = (r << 16) | x->a[i];
		q->a[i] = r / y;
		r %= y;
	}

	for (q->n = x->n; q->n > 0 && q->a[q->n - 1] == 0; q->n--);

	return r;
}

char *fmt(num_t *x)
{
	static char buf[8][65536];
	static int t[65536], z = 0;
	static num_t y;
	int i, j;
	char *s;

	if (x->n == 0)
		return "0";

	s = buf[z = (z + 1) & 7];
	if (x->sign < 0)
		*s++ = '-';

	for (y.sign = 1, y.n = j = x->n, i = 0; i < j; i++)
		y.a[i] = x->a[i];

	for (i = 0; i == 0 || y.n > 0; i++)
		t[i] = udiv1(&y, &y, 10000);

	for (j = 0; i--; j++) {
		s += sprintf(s, j ? "%.4d" : "%d", t[i]);
		while (*s) s++;
	}

	return buf[z];
}

void udiv(num_t *q, num_t *r, num_t *x, num_t *y)
{
	unsigned c, m, yh, yh2;
	int i, j, ns, rp, qp;

	assert(y->n >= 1 && y->a[y->n - 1] != 0);

	if (y->n == 1) {
		r->a[0] = udiv1(q, x, y->a[0]);
		r->n = (r->a[0] != 0) ? 1 : 0;
		return;
	}

	if (x != r)
		for (r->n = x->n, i = 0; i < x->n; i++) r->a[i] = x->a[i];

	if (x->n < y->n) {
		q->n = 0;
		return;
	}

	for (i = 0, c = y->a[y->n - 1]; ((c << i) & 0x8000) == 0; i++);
	ns = i;

	if (i > 0) {
		lshift(r, i);
		lshift(y, i);
	}

	r->a[r->n] = 0;
	q->n = qp = 1 + r->n - y->n;
	y->a[y->n] = 0;
	yh = y->a[y->n - 1];
	yh2 = y->a[y->n - 2];

	for (rp = r->n - 1; qp--; rp--) {
		c = (r->a[rp + 1] << 16) | r->a[rp];
		m = c / yh;
		if (m > 0xFFFF) m = 0xFFFF;

		while ((c - m * yh) < 0x10000 &&
		       (((c - m * yh) << 16) + r->a[rp - 1]) < (m * yh2))
			m--;

		q->a[qp] = m;

		for (c = 0, i = qp, j = 0; j <= y->n; i++, j++) {
			c += m * y->a[j];
			if (r->a[i] >= (c & 0xFFFF)) {
				r->a[i] -= c & 0xFFFF;
				c >>= 16;
			} else {
				r->a[i] = r->a[i] + 0x10000 - (c & 0xFFFF);
				c = (c >> 16) + 1;
			}
		}

		if (c != 0) {
			q->a[qp]--;

			assert(c == 1);
			for (c = 0, i = qp, j = 0; j <= y->n; i++, j++, c >>= 16)
				r->a[i] = (c += r->a[i] + y->a[j]) & 0xFFFF;
			assert(c == 1);
		}
	}

	rshift(r, ns);
	rshift(y, ns);
	while (r->n > 0 && r->a[r->n - 1] == 0) r->n--;
	while (q->n > 0 && q->a[q->n - 1] == 0) q->n--;
}

void sdiv(num_t *q, num_t *r, num_t *x, num_t *y)
{
	int s;

	if (x->n == 0) x->sign = 1;

	s = x->sign * y->sign;

	udiv(q, r, x, y);

	if (s > 0) {
		q->sign = r->sign = 1;
	} else {
		if (r->n != 0) {
			uinc(q);
			usub(r, y, r);
		}
		q->sign = -1;
		r->sign = 1;
	}
}

int main()
{
	static char s1[65536], s2[65536], s3[65536];
	static num_t t1, t2, t3, q;
	num_t *x = &t1, *y = &t2, *z = &t3, *w;
	int k;

	while (gets(s3) && sscanf(s3, " %s %s", s1, s2) == 2) {
		cvt(x, s1);
		cvt(y, s2);

		printf("%s/%s = ", fmt(x), fmt(y));

		if (x->sign < 0 && y->sign < 0)
			x->sign = y->sign = 1;

		if (y->sign < 0) {
			y->sign = 1;
			x->sign = -1;
		}

		for (k = 0;;) {
			sdiv(&q, z, x, y);
			printf("%s", fmt(&q));

			while (z->n > 0 && z->a[z->n - 1] == 0) z->n--;

			if (z->n == 0)
				break;

			printf("+1/{");
			k++;

			w = x;
			x = y;
			y = z;
			z = w;
		}

		while (k--)
			putchar('}');

		printf("\n");
	}

	return 0;
}
