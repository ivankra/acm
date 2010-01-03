#include <stdio.h>
#include <string.h>

typedef struct {
	unsigned n, a[64];
} num_t;

void sqr(num_t *x)
{
	static unsigned t[128];
	unsigned i, j, k, c;

	for (i = 2 * x->n + 2; i--;) t[i] = 0;

	for (i = 0; i < x->n; i++) {
		for (c = j = 0, k = i; j < x->n; j++, k++, c >>= 16)
			t[k] = (c += t[k] + x->a[i] * x->a[j]) & 0xFFFF;
		for (; c > 0; k++, c >>= 16)
			t[k] = (c += t[k]) & 0xFFFF;
	}

	for (i = (x->n = x->n * 2 + 2); i--;) x->a[i] = t[i];
	while (x->n > 0 && x->a[x->n - 1] == 0) x->n--;
}

void mul1(num_t *x, unsigned m, unsigned c)
{
	unsigned i;
	for (i = 0; i < x->n; i++, c >>= 16)
		x->a[i] = (c += m * x->a[i]) & 0xFFFF;
	if (c) x->a[x->n++] = c;
}

unsigned div1(num_t *x, unsigned y)
{
	unsigned i, r;
	for (r = 0, i = x->n; i--; r %= y)
		x->a[i] = (r = (r << 16) | x->a[i]) / y;
	while (x->n > 0 && x->a[x->n - 1] == 0) x->n--;
	return r;
}

void pwr(num_t *x, unsigned a, unsigned n)
{
	unsigned i;
	for (x->n = 1, x->a[0] = 1, i = 8; i--;) {
		if ((n >> i) & 1) mul1(x, a, 0);
		if (i != 0) sqr(x);
	}
}

int main()
{
	char *s, buf[1024];
	num_t x;
	int n, a;

	while (scanf("%d %d", &n, &a) == 2) {
		if (a < 1 || n < 1) {
			printf("0\n");
		} else if (a == 1) {
			printf("%d\n", n * (n + 1) / 2);
		} else {
			pwr(&x, a, n);
			mul1(&x, n * (a - 1) - 1, 1);
			mul1(&x, a, 0);
			div1(&x, (a - 1) * (a - 1));

			for ((s = buf + sizeof(buf) - 2)[0] = '\0'; x.n > 0;)
				*--s = div1(&x, 10) + '0';
			printf("%s\n", s);
		}
	}

	return 0;
}
