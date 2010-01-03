#include <stdio.h>

#define NFIB	500
#define NLIMBS	12
typedef unsigned long limb_t;
typedef unsigned long long xlimb_t;

static limb_t fib[NFIB][NLIMBS];

static void iadd(limb_t *z, const limb_t *x, const limb_t *y)
{
	register xlimb_t c;
	register int i;
	for (i = 0, c = 0; i < NLIMBS; i++, c >>= 32)
		z[i] = (limb_t)(c += (xlimb_t)x[i] + (xlimb_t)y[i]);
}

static int icmp(const limb_t *x, const limb_t *y)
{
	register int i;
	if (y == NULL) {
		for (i = 0; i < NLIMBS; i++)
			if (x[i]) return 1;
	} else {
		for (i = NLIMBS; i-- > 0;)
			if (x[i] != y[i]) return (x[i] > y[i]) ? 1 : -1;
	}
	return 0;
}

static int iset(limb_t *x, const char *s)
{
	register int i, a;
	register xlimb_t c;

	for (i = 0; i < NLIMBS; i++) x[i] = 0;

	if (s == NULL) {
		while ((a = getchar()) != EOF && (a < '0' || a > '9'));
		while (a == '0') a = getchar();
		if (a == EOF) return 0;
	} else {
		while (*s && (*s < '0' || *s > '9')) s++;
		while ((a = *s++) == '0');
	}

	while (a >= '0' && a <= '9') {
		for (c = (a - '0'), i = 0; i < NLIMBS; i++, c >>= 32)
			x[i] = (limb_t)(c += (xlimb_t)x[i] * (xlimb_t)10);
		a = s ? (*s++) : (getchar());
	}

	return 1;
}

int fib_less(const limb_t *x)
{
	int i, j, k, c;

	if (icmp(x, fib[0]) <= 0) return 0;

	for (i = 1, j = NFIB - 1; i < j;)
		if ((c = icmp(fib[k = ((i + j) >> 1)], x)) == 0)
			return (k - 1);
		else if (c < 0)
			i = k + 1;
		else
			j = k - 1;
	i -= 3;
	if (i < 1) i = 1;

	while (icmp(fib[i], x) < 0)
		i++;

	return (i - 1);
}

int main()
{
	static limb_t x[NLIMBS], y[NLIMBS];
	int i, j;

	iset(fib[0], "1");
	iset(fib[1], "1");
	for (i = 2; i < NFIB; i++)
		iadd(fib[i], fib[i - 2], fib[i - 1]);

	while (iset(x, NULL) && iset(y, NULL)) {
		if (icmp(x, NULL) == 0 && icmp(y, NULL) == 0)
			break;

		iadd(y, y, fib[0]);

		i = fib_less(x);
		j = fib_less(y);

		printf("%d\n", j - i);
	}

	return 0;
}
