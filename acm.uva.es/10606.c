#include <stdio.h>
#include <string.h>
#include <assert.h>

typedef struct {
	unsigned n, a[16];
} num_t;

typedef unsigned long long u64;

void sqr(num_t *z, num_t *x)
{
	u64 c;
	unsigned i, j, k;

	z->n = x->n * 2 + 1;
	for (i = 0; i < z->n; i++)
		z->a[i] = 0;

	for (i = 0; i < x->n; i++) {
		for (j = 0, k = i, c = 0; j < x->n; j++, k++, c >>= 32) {
			c += (u64)z->a[k] + (u64)x->a[i] * (u64)x->a[j];
			z->a[k] = (unsigned)c;
		}
		for (; c != 0; k++, c >>= 32)
			z->a[k] = (unsigned)(c += (u64)z->a[k]);
	}

	while (z->n > 0 && z->a[z->n - 1] == 0) z->n--;
}

unsigned isqrt(unsigned a)
{
	unsigned x, y, i;
	for (x = 0, i = 16; i--;) {
		y = x | (1 << i);
		if ((y * y) <= a) x = y;
	}
	return x;
}

void copy(num_t *x, num_t *y)
{
	x->n = y->n;
	memcpy(x->a, y->a, y->n * sizeof(y->a[0]));
}

void muladd(num_t *x, unsigned m, unsigned c0)
{
	unsigned i;
	u64 c;

	for (i = 0, c = c0; i < x->n; i++, c >>= 32) {
		c += (u64)x->a[i] * (u64)m;
		x->a[i] = (unsigned)c;
	}

	if (c != 0)
		x->a[x->n++] = (unsigned)c;
}

void set(num_t *x, char *s)
{
	unsigned a, m;

	while (*s == '0') s++;

	for (x->n = 0, a = 0, m = 1; *s;) {
		a = a * 10 + *s++ - '0';
		m *= 10;
		if (m == 1000000000) {
			muladd(x, m, a);
			m = 1;
			a = 0;
		}
	}

	if (m > 1)
		muladd(x, m, a);
}

char *fmt(num_t *x)
{
	static char buf[4][4096];
	static int Z = 0;
	static num_t t;
	char *s;
	u64 r;
	unsigned i;

	copy(&t, x);
	Z = (Z + 1) & 3;
	for (*(s = buf[Z] + 4094) = '\0'; t.n > 0;) {
		for (i = t.n, r = 0; i--;) {
			r = (r << 32) | (u64)t.a[i];
			t.a[i] = r / 1000000000ULL;
			r %= 1000000000ULL;
		}

		for (i = 0; i < 9; i++, r /= 10)
			*--s = (unsigned)(r % 10) + '0';

		while (t.n > 0 && t.a[t.n - 1] == 0) t.n--;
	}

	while (*s == '0') s++;

	return (*s == '\0') ? "0" : s;
}

int cmp(num_t *x, num_t *y)
{
	unsigned i;

	if (x->n != y->n)
		return (x->n > y->n) ? 1 : -1;

	for (i = x->n; i--;)
		if (x->a[i] != y->a[i]) return (x->a[i] > y->a[i]) ? 1 : -1;

	return 0;
}

void add(num_t *x, num_t *y)
{
	unsigned i;
	u64 c;

	while (x->n < y->n) x->a[x->n++] = 0;

	for (i = 0, c = 0; i < y->n; i++, c >>= 32) {
		c += (u64)x->a[i] + (u64)y->a[i];
		x->a[i] = (unsigned)c;
	}

	for (; c > 0 && i < x->n; i++, c >>= 32) {
		c += (u64)x->a[i];
		x->a[i] = (unsigned)c;
	}

	if (c > 0)
		x->a[x->n++] = (unsigned)c;
}

void dec(num_t *x)
{
	int i;
	for (i = 0;; i++) {
		if (x->a[i] == 0) {
			x->a[i] = 0xFFFFFFFF;
		} else {
			x->a[i]--;
			break;
		}
	}
	while (x->n > 0 && x->a[x->n - 1] == 0) x->n--;
}

void lshift(num_t *x, unsigned s)
{
	unsigned i;
	u64 c;

	for (i = 0, c = 0; i < x->n; i++, c >>= 32) {
		c |= ((u64)x->a[i]) << s;
		x->a[i] = (unsigned)c;
	}

	if (c != 0)
		x->a[x->n++] = (unsigned)c;
}

void rshift(num_t *x, unsigned s)
{
	unsigned i;
	u64 c;
	for (i = x->n, c = 0; i--; c <<= 32) {
		c |= (u64)x->a[i];
		x->a[i] = (unsigned)(c >> s);
	}
	while (x->n > 0 && x->a[x->n - 1] == 0) x->n--;
}

unsigned div1(num_t *q, num_t *x, unsigned y)
{
	unsigned i;
	u64 r;

	for (i = x->n, r = 0; i--;) {
		r = (r << 32) | (u64)x->a[i];
		q->a[i] = (unsigned)(r / (u64)y);
		r %= (u64)y;
	}

	for (q->n = x->n; q->n > 0 && q->a[q->n - 1] == 0; q->n--);

	return (unsigned)r;
}

void div(num_t *q, num_t *r, num_t *x, num_t *y)
{
	unsigned yh, yh2;
	int i, j, ns, rp, qp;
	u64 c, m;

	assert(y->n >= 1 && y->a[y->n - 1] != 0);

	if (y->n == 1) {
		r->a[0] = div1(q, x, y->a[0]);
		r->n = (r->a[0] != 0) ? 1 : 0;
		return;
	}

	if (x != r)
		for (r->n = x->n, i = 0; i < x->n; i++) r->a[i] = x->a[i];

	if (x->n < y->n) {
		q->n = 0;
		return;
	}

	for (i = 0, yh = y->a[y->n - 1]; ((yh << i) & 0x80000000) == 0; i++);
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
		c = (((u64)(r->a[rp + 1])) << 32) | (u64)(r->a[rp]);
		m = c / (u64)yh;
		if (m > 0xFFFFFFFF) m = 0xFFFFFFFF;

		while ((c - m * (u64)yh) < 0x100000000ULL &&
		       (((c - m * (u64)yh) << 32) + (u64)r->a[rp - 1]) < (m * (u64)yh2))
			m--;

		q->a[qp] = m;

		for (c = 0, i = qp, j = 0; j <= y->n; i++, j++) {
			c += m * (u64)y->a[j];
			if (r->a[i] >= (unsigned)(c & 0xFFFFFFFFULL)) {
				r->a[i] -= (unsigned)(c & 0xFFFFFFFF);
				c >>= 32;
			} else {
				r->a[i] += (unsigned)(0x100000000ULL - (c & 0xFFFFFFFFULL));
				c = (c >> 32) + 1;
			}
		}

		if (c != 0) {
			q->a[qp]--;

			assert(c == 1);
			for (c = 0, i = qp, j = 0; j <= y->n; i++, j++, c >>= 32) {
				c += (u64)r->a[i] + (u64)y->a[j];
				r->a[i] = (unsigned)c;
			}
			assert(c == 1);
		}
	}

	rshift(r, ns);
	rshift(y, ns);
	while (r->n > 0 && r->a[r->n - 1] == 0) r->n--;
	while (q->n > 0 && q->a[q->n - 1] == 0) q->n--;
}

num_t R, Q;

int check()
{
	static unsigned q0;
	unsigned i;
	u64 t;

	i = R.n << 1;
	if (i < Q.n) return -1;
	if (i > (Q.n + 1)) return 1;

	if (i == (Q.n + 1))
		q0 = 0;
	else
		q0 = Q.a[Q.n - 1];

	t = R.a[R.n - 1];
	t *= t;
	t >>= 32;

	if ((t + 1) < q0)
		return -1;
	else if (t > q0)
		return 1;

	return 2;
}

void solve()
{
	static num_t A, B, C;
	int i;
	u64 t;

	if (Q.n <= 1) {
		t = isqrt(Q.a[0]);
		printf("%llu\n", t*t);
		return;
	}

	B.n = (Q.n + 1) >> 1;
	for (i = 0; i < B.n; i++) B.a[i] = 0;
	B.a[B.n++] = 1;

	A.n = (Q.n - 1) >> 1;
	for (i = 0; i < A.n; i++) A.a[i] = 0;
	if (A.n > 0) A.a[A.n - 1] = 1;

	while (cmp(&A, &B) < 0) {
		for (i = 0, t = 1; i < A.n; i++, t >>= 32) {
			t += (u64)A.a[i] + (u64)B.a[i];
			R.a[i] = (unsigned)t;
		}

		for (; i < B.n; i++, t >>= 32) {
			t += (u64)B.a[i];
			R.a[i] = (unsigned)t;
		}

		for (R.n = B.n; i--;) {
			t = (t << 32) | (u64)R.a[i];
			R.a[i] = (t >> 1);
			t &= 1;
		}

		while (R.a[R.n - 1] == 0) R.n--;

		i = check();

		if (i == 0) {
			copy(&A, &R);
			break;
		} else if (i == -1) {
			copy(&A, &R);
		} else if (i == 1) { 
			copy(&B, &R);
			dec(&B);
		} else {
			break;
		}
	}

	for (;;) {
		div(&A, &C, &Q, &B);
		add(&A, &B);
		rshift(&A, 1);
		if (cmp(&A, &B) >= 0) break;
		copy(&B, &A);
	}

	sqr(&A, &B);
	printf("%s\n", fmt(&A));
}

int main()
{
	static char s[4096];

	while (scanf(" %[0-9]", s) == 1) {
		set(&Q, s);
		if (Q.n == 0) break;
		solve();
	}

	return 0;
}
