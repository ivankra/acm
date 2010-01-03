#include <stdio.h>
#include <string.h>

#define SCALE	28
#define NDIG	48

typedef struct {
	int a[NDIG];
} num_t;

static void set(num_t *x, int t)
{
	memset(x, 0, sizeof(num_t));
	x->a[SCALE] = t;
}

static void add(num_t *z, num_t *x)
{
	register int i, c;

	for (c = 0, i = 0; i < NDIG; i++) {
		c += z->a[i] + x->a[i];

		if (c < 10) {
			z->a[i] = c;
			c = 0;
		} else {
			z->a[i] = c - 10;
			c = 1;
		}
	}
}

static void div1(num_t *z, int d)
{
	register int i, t;

	for (i = NDIG - 1, t = 0; i >= 0; i--) {
		t = t * 10 + z->a[i];
		z->a[i] = t / d;
		t %= d;
	}
}

static void muladd1(num_t *z, num_t *x, int m)
{
	register int i, c;

	for (i = 0, c = 0; i < NDIG; i++) {
		c += z->a[i] + x->a[i] * m;
		z->a[i] = c % 10;
		c /= 10;
	}
}

char *fmt(num_t *x)
{
	static char buf[16][1024];
	static int z = 0;
	char *s;
	int i;

	s = buf[z = (z + 1) & 15];

	for (i = NDIG - 1; i > SCALE && x->a[i] == 0; i--);

	for (; i >= SCALE; i--)
		*s++ = x->a[i] + '0';

	for (*s++ = '.', i = 0; i < 3; i++)
		*s++ = x->a[SCALE - 1 - i] + '0';
	*s = '\0';

	return buf[z];
}

int a[8][8], n;

void solve()
{
	static num_t b[8][8], c[8][8], r[8][8], z;
	int i, j, k, s;

	memset(r, 0, sizeof(r));

	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			set(&b[i][j], (i == j) ? 1 : 0);

	for (s = 1; s < 120; s++) {
		for (i = 0; i < n; i++)
			for (j = 0; j < n; j++)
				add(&r[i][j], &b[i][j]);

		for (i = 0; i < n; i++) {
			for (j = 0; j < n; j++) {
				for (set(&c[i][j], 0), k = 0; k < n; k++)
					muladd1(&c[i][j], &b[i][k], a[k][j]);
				div1(&c[i][j], s);
			}
		}

		memcpy(b, c, sizeof(c));
	}

	set(&z, 0);
	z.a[SCALE - 4] = 5;

	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			add(&r[i][j], &z);
			printf(((j + 1) < n) ? "%s " : "%s\n", fmt(&r[i][j]));
		}
	}
}

void approx()
{
	static long double b[8][8], c[8][8], d[8][8], r[8][8], m;
	int i, j, k, s;

	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			d[i][j] = (long double)a[i][j];

	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			r[i][j] = (i == j) ? 1. : 0.;

	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			b[i][j] = d[i][j];

	for (s = 1, m = 1.; s < 120; s++) {
		for (i = 0; i < n; i++)
			for (j = 0; j < n; j++)
				r[i][j] += b[i][j] / m;

		for (i = 0; i < n; i++)
			for (j = 0; j < n; j++)
				for (c[i][j] = 0., k = 0; k < n; k++)
					c[i][j] += b[i][k] * d[k][j];

		for (i = 0; i < n; i++)
			for (j = 0; j < n; j++)
				b[i][j] = c[i][j];

		m *= (long double)(s + 1);
	}

	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			printf(((j + 1) < n) ? "%.3Lf " : "%.3Lf\n", r[i][j]);
}

int main()
{
	int i, j, t;

	for (scanf("%d", &t); t-- > 0 && scanf("%d", &n) == 1;) {
		for (i = 0; i < n; i++)
			for (j = 0; j < n; j++)
				scanf("%d", &a[i][j]);

		if (n <= 7)
			approx();
		else
			solve();

		if (t > 0)
			printf("\n");
	}

	return 0;
}
