#include <stdio.h>
#include <string.h>

#define NLIMBS 6

typedef unsigned long u_int32_t;
typedef unsigned long long u_int64_t;

typedef struct mp {
	u_int32_t d[NLIMBS];
} mp_t;

static mp_t c_zero, c_one;

static void mp_add(mp_t *z, const mp_t *x, const mp_t *y)
{
	register int i;
	register u_int64_t c;

	for (i = 0, c = 0; i < NLIMBS; i++, c >>= 32) {
		c += (u_int64_t)x->d[i] + (u_int64_t)y->d[i];
		z->d[i] = (u_int32_t)(c);
	}
}

static void mp_sub(mp_t *z, const mp_t *x, const mp_t *y)
{
	register int i;
	register u_int64_t c;

	for (i = 0, c = 1; i < NLIMBS; i++, c >>= 32) {
		c += (u_int64_t)x->d[i] + (((u_int64_t)y->d[i]) ^ 0xFFFFFFFFULL);
		z->d[i] = (u_int32_t)(c);
	}
}

static void mp_set(mp_t *z, const mp_t *x)
{
	register int i;

	for (i = 0; i < NLIMBS; i++)
		z->d[i] = x->d[i];
}

static void mp_load(mp_t *x, int n)
{
	int i;
	for (x->d[0] = n, i = 1; i < NLIMBS; i++)
		x->d[i] = 0;
}

static unsigned mp_div1(mp_t *x, unsigned d)
{
	register int i;
	register u_int64_t c;

	for (c = 0, i = NLIMBS - 1; i >= 0; i--) {
		c = (c << 32) | (u_int64_t)x->d[i];
		x->d[i] = (u_int32_t)(c / (u_int64_t)d);
		c %= (u_int64_t)d;
	}

	return c;
}

static char *mp_print(mp_t *x)
{
	static mp_t t;
	static char buf1[1024], buf2[1024];
	int i, j;

	mp_set(&t, x);

	for (i = 0;;) {
		buf1[i++] = mp_div1(&t, 10) + '0';

		for (j = 0; j < NLIMBS; j++)
			if (t.d[j] != 0) break;
		if (j >= NLIMBS) break;
	}

	for (j = 0; i-- > 0;)
		buf2[j++] = buf1[i];
	buf2[j] = '\0';
	return buf2;
}

/*---------------------------------------------------------------------------*/

#define MAXM 40

static char gtab_u[4][MAXM][MAXM][MAXM], ftab_u[4][MAXM][MAXM][MAXM];
static mp_t gtab[4][MAXM][MAXM][MAXM], ftab[4][MAXM][MAXM][MAXM];

static mp_t *g(int s, int a, int b, int c)
{
	if (a < 0 || b < 0 || c < 0)
		return &c_zero;

#define GVAL (&gtab[s][a][b][c])

	if (gtab_u[s][a][b][c])
		return GVAL;

	gtab_u[s][a][b][c] = 1;

	if ((a + b + c) == 1) {
		if ((s == 1 && a == 1) || (s == 2 && b == 1) ||
		    (s == 3 && c == 1)) {
			mp_load(GVAL, 0);
			return GVAL;
		}

		mp_load(GVAL, 1);
		return GVAL;
	}

	if (s == 1) {
		mp_add(GVAL, g(2, a, b - 2, c), g(3, a, b, c - 2));
		return GVAL;
	} else if (s == 2) {
		mp_add(GVAL, g(1, a - 2, b, c), g(3, a, b, c - 2));
		return GVAL;
	} else {
		mp_add(GVAL, g(1, a - 2, b, c), g(2, a, b - 2, c));
		return GVAL;
	}
}

static mp_t *f(int s, int a, int b, int c)
{
	if (a < 0 || b < 0 || c < 0)
		return &c_zero;

#define FVAL (&ftab[s][a][b][c])

	if (ftab_u[s][a][b][c])
		return FVAL;

	ftab_u[s][a][b][c] = 1;

	if ((a + b + c) <= 0) {
		mp_load(FVAL, 0);
		return FVAL;
	}

	if ((a + b + c) == 1) {
		if (a == 1 && s != 1)
			mp_load(FVAL, 1);
		else
			mp_load(FVAL, 0);
		return FVAL;
	}

	if (s == 1)
		mp_add(FVAL, f(2, a, b - 1, c), f(3, a, b, c - 1));
	else if (s == 2)
		mp_add(FVAL, f(1, a - 1, b, c), f(3, a, b, c - 1));
	else
		mp_add(FVAL, f(1, a - 1, b, c), f(2, a, b - 1, c));
	return FVAL;
}


int main()
{
	int n, m, c, t;
	mp_t *fv, *gv, u;

	mp_load(&c_zero, 0);
	mp_load(&c_one, 1);

	memset(gtab_u, 0, sizeof(gtab_u));
	memset(ftab_u, 0, sizeof(ftab_u));

	scanf("%d", &t);

	for (c = 1; c <= t && scanf("%d", &n) == 1; c++) {
if (n == 1) { printf("Case %d: 1\n", c); continue; }

		m = (n - 1) / 3;

		fv = f(1, m, m, m);
		gv = g(1, m - 1, m, m);

		mp_sub(&u, fv, gv);
		mp_div1(&u, 2);
		mp_add(&u, &u, gv);

/*
printf("(((%s - ", mp_print(fv));
printf("%s) / 2) + ", mp_print(gv));
printf("%s) -", mp_print(gv));
printf(" %s\n", mp_print(&u));
*/
		printf("Case %d: %s\n", c, mp_print(&u));
	}

	return 0;
}
