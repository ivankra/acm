#include <stdio.h>
#include <string.h>

#define RADIX 1000000000ULL

struct num {
	int exp, prec;
	u_int32_t d[32];
};

static void mul(struct num *r, struct num *x, struct num *y)
{
	int i, j;
	u_int64_t c;

	r->exp = x->exp + y->exp;

	r->prec = x->prec + y->prec;
	for (i = 0; i < r->prec; i++)
		r->d[i] = 0;

	for (i = 0; i < x->prec; i++) {
		for (j = 0, c = 0; j < y->prec; j++) {
			c += (u_int64_t)x->d[i] * (u_int64_t)y->d[j];
			c += (u_int64_t)r->d[i + j];
			if (c >= RADIX) {
				r->d[i + j] = (u_int32_t)(c % RADIX);
				c /= RADIX;
			} else {
				r->d[i + j] = (u_int32_t)c;
				c = 0;
			}
		}

		for (j += i; c > 0;) {
			c += (u_int64_t)r->d[j];
			if (c >= RADIX) {
				r->d[j] = (u_int32_t)(c % RADIX);
				c /= RADIX;
			} else {
				r->d[j] = (u_int32_t)c;
				break;
			}
		}
	}

	while (r->prec > 1 && r->d[r->prec - 1] == 0)
		r->prec--;

	if (r->prec == 1 && r->d[0] == 0)
		r->exp = 0;
}

static void expon(struct num *r, struct num *a, int n)
{
	static struct num tmp;

	if (n == 1) {
		memcpy(r, a, sizeof(struct num));
		return;
	}

	r->exp = 0;
	r->prec = 1;
	r->d[0] = 1;

	for (; n > 0; n >>= 1) {
		if (n & 1) {
			mul(&tmp, r, a);
			memcpy(r, &tmp, sizeof(struct num));
		}

		if (n > 1) {
			mul(&tmp, a, a);
			memcpy(a, &tmp, sizeof(struct num));
		}
	}
}

static void parse(struct num *a, char *s)
{
	int p;

	memset(a, '\0', sizeof(struct num));

	for (p = 0; *s; s++) {
		if (*s == '.') {
			p = 1;
		} else if (*s >= '0' && *s <= '9') {
			if (p) a->exp--;
			a->d[0] = a->d[0] * 10 + *s - '0';
		}
	}

	a->prec = 1;

	if (a->d[0] == 0) {
		a->exp = 0;
	} else {
		while ((a->d[0] % 10) == 0) {
			a->d[0] /= 10;
			a->exp++;
		}
	}
}

static void print(struct num *a)
{
	static char s[1024], u[1024];
	char *p;
	int i, j, k, t;

	p = s;

	if (a->exp > 0)
		for (i = 0; i < a->exp; i++) *p++ = '0';

	for (i = 0, k = 0; i < a->prec; i++) {
		for (j = 0, t = a->d[i]; j < 9; j++, k++, t /= 10) {
			if (a->exp < 0 && k == -(a->exp)) *p++ = '.';
			*p++ = (t % 10) + '0';
		}
	}

	if (a->exp < 0 && k < -(a->exp)) {
		while (k < -(a->exp))
			*p++ = '0', k++;
		*p++ = '.';
	}

	for (p--; p > s && *p == '0'; p--);

	for (i = 0; p >= s;)
		u[i++] = *p--;

	u[i] = '\0';

	printf("%s\n", u);
}

int main()
{
	static struct num x, y;
	static char s[256];
	int n;

	while (scanf(" %[0-9.] %d", s, &n) == 2) {
		parse(&x, s);
		expon(&y, &x, n);
		print(&y);
	}

	return 0;
}
