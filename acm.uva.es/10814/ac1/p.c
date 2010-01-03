#include <stdio.h>
#include <string.h>

#define NLIMBS 8

typedef unsigned short num_t[NLIMBS];

static void sub(num_t x, num_t y)
{
	int i, c;

	for (i = 0, c = 1; i < NLIMBS; i++, c >>= 16) {
		c += (unsigned)x[i] + (((unsigned)y[i]) ^ 0xFFFF);
		x[i] = c & 0xFFFF;
	}
}

static void shl(num_t a)
{
	int i, c;

	for (i = 0, c = 0; i < NLIMBS; i++) {
		c = (((int)a[i]) << 1) | (c & 1);
		a[i] = c & 0xFFFF;
		c >>= 16;
	}

}

static void shr(num_t a)
{
	int i, c;

	for (i = NLIMBS - 1, c = 0; i >= 0; i--) {
		c = ((c & 1) << 16) | (int)a[i];
		a[i] = ((c >> 1) & 0xFFFF);
	}
}

static void set(num_t a, char *s)
{
	int i, c;

	for (memset(a, '\0', sizeof(num_t)); *s; s++)
		for (i = 0, c = *s - '0'; i < NLIMBS; i++, c >>= 16)
			a[i] = (c += 10 * (int)a[i]) & 0xFFFF;
}

static int cmp(num_t x, num_t y)
{
	int i;

	if (y == NULL) {
		for (i = 0; i < NLIMBS; i++)
			if (x[i]) return 1;
	} else {
		for (i = NLIMBS - 1; i >= 0; i--)
			if (x[i] != y[i]) return (x[i] > y[i]) ? 1 : -1;
	}

	return 0;
}

static char *fmt(char *s, num_t x)
{
	static char buf[1024];
	int i, k, r;

	for (k = 0; cmp(x, NULL) != 0 || k == 0;) {
		for (i = NLIMBS - 1, r = 0; i >= 0; i--) {
			r = (r << 16) | x[i];
			x[i] = r / 10;
			r %= 10;
		}

		buf[k++] = r + '0';
	}

	for (i = 0; k-- > 0;)
		s[i++] = buf[k];
	s[i] = '\0';

	return s;
}

static void div(num_t a, num_t d)
{
	static num_t q;
	int k;

	memset(q, '\0', sizeof(num_t));
	for (k = 0; cmp(a, d) >= 0; k++, shl(d));

	while (k-- > 0) {
		shr(d);

		if (cmp(a, d) >= 0) {
			sub(a, d);
			q[k >> 4] |= 1 << (k & 15);
		}
	}

	memcpy(a, q, sizeof(num_t));
}

static void reduce(num_t p, num_t q)
{
	static num_t x, y;

	if (cmp(p, NULL) == 0 || cmp(q, NULL) == 0)
		return;

	while (((p[0] | q[0]) & 1) == 0) {
		shr(p);
		shr(q);
	}

	memcpy(x, p, sizeof(num_t));
	memcpy(y, q, sizeof(num_t));

	for (;;) {
		if (cmp(x, NULL) == 0) {
			div(p, y);
			div(q, y);
			return;
		}

		if (cmp(y, NULL) == 0) {
			div(p, x);
			div(q, x);
			return;
		}

		while ((x[0] & 1) == 0)
			shr(x);

		while ((y[0] & 1) == 0)
			shr(y);

		if (cmp(x, y) >= 0)
			sub(x, y);
		else
			sub(y, x);
	}
}

int main()
{
	static char s[1024], t[1024];
	num_t x, y;
	int n;

	for (scanf("%d", &n); n-- > 0 && scanf(" %[0-9] / %[0-9]", s, t) == 2;) {
		set(x, s);
		set(y, t);

		reduce(x, y);

		printf("%s / %s\n", fmt(s, x), fmt(t, y));
	}

	return 0;
}
