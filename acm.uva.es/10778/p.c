#include <stdio.h>

typedef long long num;

int isqrt(num a)
{
	num x, y;

	for (x = a; x > 1; x = y)
		if ((y = (x + (a / x)) >> 1) >= x) break;

	return (int)x;
}

int divisors(num r[], num x)
{
	static num a[64], b[64];
	static int c[64], e[64];
	int i, k, n;

	if (x == 0) {
		r[0] = 1;
		r[1] = 0;
		return 1;
	}

	if (x < 0)
		x = -x;

	if ((x & 1) == 0)
		for (b[0] = 2, e[0] = 0, n = 1; (x & 1) == 0; x >>= 1) e[0]++;
	else
		n = 0;

	for (i = 3, k = isqrt(x) + 1; i <= k; i += 2) {
		if ((x % i) == 0) {
			for (b[n] = i, e[n] = 1, x /= i; (x % i) == 0; e[n]++)
				x /= i;
			n++;
			k = isqrt(x);
		}
	}

	if (x > 1)
		b[n] = x, e[n] = 1, n++;

	for (k = 0, i = 0; i < n; i++)
		a[i] = 1, c[i] = 0;

	do {
		for (r[k] = 1, i = 0; i < n; i++)
			r[k] *= a[i];

		for (k++, i = 0; i < n; i++) {
			if (++c[i] <= e[i]) {
				a[i] *= b[i];
				break;
			} else {
				a[i] = 1;
				c[i] = 0;
			}
		}
	} while (i < n);

	r[k] = 0;
	return k;
}

void sort(num a[], int n)
{
	int i, j;
	num t;

	for (i = 1; i < n; i++) {
		for (t = a[i], j = i - 1; j >= 0 && a[j] > t; j--)
			a[j + 1] = a[j];
		a[j + 1] = t;
	}
}

num gcd(num x, num y)
{
	int k;

	for (k = 0; ((x | y) & 1) == 0; k++, x >>= 1, y >>= 1);

	for (;;) {
		if (x == 0) return (y << k);
		if (y == 0) return (x << k);

		while ((x & 1) == 0) x >>= 1;
		while ((y & 1) == 0) y >>= 1;

		if (x > y)
			x -= y;
		else
			y -= x;
	}
}

struct poly {
	unsigned m, n, a[1024];
} plist[16];

unsigned moduli[] = { 32749, 32719, 32693, 32531, 0 };

num roots[1024];
int nroots;

unsigned eval(struct poly *z, num p0, num q0)
{
	static unsigned pw[1024], qw[1024];
	unsigned i, p, q;

	if (p0 >= 0)
		p = p0 % z->m;
	else {
		p = z->m - ((-p0) % z->m);
		if (p == z->m) p = 0;
	}

	if (q0 >= 0)
		q = q0 % z->m;
	else {
		q = z->m - ((-q0) % z->m);
		if (q == z->m) q = 0;
	}

	for (pw[0] = 1, i = 0; i < z->n; i++)
		pw[i + 1] = (pw[i] * p) % z->m;

	for (qw[0] = 1, i = 0; i < z->n; i++)
		qw[i + 1] = (qw[i] * q) % z->m;

	for (p = 0, i = 0; i <= z->n; i++)
		p = (p + ((z->a[i] * pw[z->n - i]) % z->m) * qw[i]) % z->m;

	return p;
}

void divpoly(struct poly *z, num p0, num q0)
{
	static unsigned pw[1024], qw[1024], b[1024];
	unsigned i, j, p, q;

	if (p0 >= 0)
		p = p0 % z->m;
	else {
		p = z->m - ((-p0) % z->m);
		if (p == z->m) p = 0;
	}

	if (q0 >= 0)
		q = q0 % z->m;
	else {
		q = z->m - ((-q0) % z->m);
		if (q == z->m) q = 0;
	}

	for (pw[0] = 1, i = 0; i < z->n; i++)
		pw[i + 1] = (pw[i] * p) % z->m;

	for (qw[0] = 1, i = 0; i < z->n; i++)
		qw[i + 1] = (qw[i] * q) % z->m;

	for (i = 0; i <= z->n; i++)
		for (b[i] = 0, j = 0; j <= i; j++)
			b[i] = (b[i] + ((z->a[j] * pw[i - j]) % z->m) * qw[z->n - i + j]) % z->m;

	for (i = 0; i <= z->n; i++)
		z->a[i] = b[i];
	z->n--;
}

void initpoly(num coef[], int deg)
{
	int i, j;

	for (i = 0; moduli[i]; i++) {
		plist[i].m = moduli[i];
		plist[i].n = deg;

		for (j = 0; j <= deg; j++) {
			if (coef[j] >= 0)
				plist[i].a[j] = coef[j] % (num)moduli[i];
			else {
				plist[i].a[j] = moduli[i] - ((-coef[j]) % (num)moduli[i]);
				if (plist[i].a[j] == moduli[i]) plist[i].a[j] = 0;
			}
		}
	}
}

int check(num p, num q)
{
	int i;

	for (i = 0; moduli[i]; i++)
		if (eval(&plist[i], p, q) != 0) return 0;

	return 1;
}

void divall(num p, num q)
{
	int i;

	for (i = 0; moduli[i]; i++)
		divpoly(&plist[i], p, q);
}

void solve(num coef[], int deg)
{
	static num p[16384], q[16384];
	int i, j;

	nroots = 0;

	while (deg > 0 && coef[deg] == 0) {
		roots[nroots++] = 0;
		deg--;
	}

	if (deg < 1)
		return;

	initpoly(coef, deg);

	divisors(p, coef[deg]);
	divisors(q, coef[0]);

	for (i = 0; p[i] != 0; i++) {
		for (j = 0; q[j] != 0; j++) {
			if (gcd(p[i], q[j]) != 1)
				continue;

			while (check(p[i], q[j])) {
				roots[nroots++] = (coef[0] / q[j]) * p[i];
				divall(p[i], q[j]);
			}

			while (check(-p[i], q[j])) {
				roots[nroots++] = (coef[0] / q[j]) * (-p[i]);
				divall(-p[i], q[j]);
			}
		}
	}
}

int main()
{
	static num coef[1024];
	int deg, i, t;

	for (t = 0; scanf("%d %lld", &deg, &coef[0]) == 2 && deg > 0; t++) {
		if (t > 0)
			printf("\n");

		for (i = 1; i <= deg; i++) {
			scanf("%lld", &coef[i]);
			if (i & 1) coef[i] = -coef[i];
		}

		solve(coef, deg);

		if (nroots == 0)
			printf("No solution.\n");
		else {
			sort(roots, nroots);
			for (i = 0; i < nroots; i++)
				printf(i ? " %lld" : "%lld", roots[i]);
			printf("\n");
		}
	}

	return 0;
}
