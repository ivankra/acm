#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	unsigned n, a[63];
} num_t;

num_t *zero, *one, *ftab[64][64], *htab[64][64], *gtab[64][64][64];

void muladd(num_t *z, num_t *x, num_t *y)
{
	unsigned i, j, k, c;

	for (k = x->n + y->n + 1; z->n < k;) z->a[z->n++] = 0;

	for (i = 0; i < x->n; i++) {
		for (j = c = 0, k = i; j < y->n; j++, k++, c >>= 16)
			z->a[k] = (c += z->a[k] + x->a[i] * y->a[j]) & 0xFFFF;
		for (; c > 0; k++, c >>= 16)
			z->a[k] = (c += z->a[k]) & 0xFFFF;
	}

	while (z->n > 0 && z->a[z->n - 1] == 0) z->n--;
}

void copy(num_t *x, num_t *y)
{
	int i;
	for (x->n = y->n, i = 0; i < x->n; i++) x->a[i] = y->a[i];
}

void add(num_t *z, num_t *x)
{
	unsigned i, c;

	while (z->n < x->n) z->a[z->n++] = 0;

	for (i = c = 0; i < x->n; i++, c >>= 16)
		z->a[i] = (c += x->a[i] + z->a[i]) & 0xFFFF;

	for (; c > 0 && i < x->n; i++, c >>= 16)
		z->a[i] = (c += z->a[i]) & 0xFFFF;

	if (c) z->a[z->n++] = c;
}

num_t *make(unsigned x)
{
	static num_t *buf = NULL;
	static unsigned left = 0;

	if (left == 0) {
		left = 65536;
		buf = (num_t *)malloc(left * sizeof(num_t));
	}

	buf->a[0] = x;
	buf->n = x ? 1 : 0;
	return buf++;
}

void mulby(num_t *x, num_t *y)
{
	static num_t t;
	copy(&t, x);
	x->n = 0;
	muladd(x, &t, y);
}

unsigned div1(num_t *x, unsigned d)
{
	unsigned i, r;
	for (r = 0, i = x->n; i--; r %= d)
		x->a[i] = (r = (r << 16) | x->a[i]) / d;
	while (x->n > 0 && x->a[x->n - 1] == 0) x->n--;
	return r;
}

char *fmt(num_t *x)
{
	static num_t t;
	static char buf[65536];
	char *s;

	copy(&t, x);
	for (*(s = buf + sizeof(buf) - 2) = '\0'; t.n > 0 || *s == '\0';)
		*--s = div1(&t, 10) + '0';
	return s;
}

num_t *H(int, int);

/* G(n,d,k) = [H(n,d)]^k  == \sum_{0 <= a_1,a_2,...,a_k <= d} F(n,a_1)...F(n,a_k)
   G(n,d,0) = 1 */
num_t *G(int n, int d, int k)
{
	if (k == 0) return one;
	if (d < 0) return zero;
	if (gtab[n][d][k]) return gtab[n][d][k];
	gtab[n][d][k] = make(0);
	muladd(gtab[n][d][k], G(n, d, k - 1), H(n, d));
	return gtab[n][d][k];
}

/* F(n,0) = 1
   F(n,d) = F(n,d-1) \sum_{0 <= k < n} G(n,d-2,k) G(n,d-1,n-1-k) */
num_t *F(int n, int d)
{
	int k;

	if (ftab[n][d]) return ftab[n][d];
	if (d == 0) return one;

	ftab[n][d] = make(0);
	for (k = 0; k < n; k++)
		muladd(ftab[n][d], G(n, d - 2, k), G(n, d - 1, n - 1 - k));

	mulby(ftab[n][d], F(n, d - 1));
	return ftab[n][d];
}

/* H(n,d) = \sum_{0 <= i <= d} F(n,i) */
num_t *H(int n, int d)
{
	if (d < 0) return zero;
	if (htab[n][d]) return htab[n][d];
	htab[n][d] = make(0);
	copy(htab[n][d], H(n, d - 1));
	add(htab[n][d], F(n, d));
	return htab[n][d];
}

int main()
{
	int n, d;

	memset(ftab, 0, sizeof(ftab));
	memset(gtab, 0, sizeof(gtab));
	memset(htab, 0, sizeof(htab));
	zero = make(0);
	one = make(1);

	while (scanf("%d %d", &n, &d) == 2 && (n | d) != 0)
		printf("%d %d %s\n", n, d, fmt(F(n, d)));

	return 0;
}
