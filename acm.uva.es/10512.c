#include <stdio.h>

long long p, q;
int solx[1024], soly[1024], nsol;

long long isqrt(long long a)
{
	long long x, y;

	for (x = a; x > 1LL; x = y) {
		y = (x + (a / x)) >> 1;
		if (y >= x) break;
	}

	return x;
}

int perfect(long long a, long long *s)
{
	long long r;

	if (a < 0)
		return 0;

	r = isqrt(a);
	if ((r * r) != a)
		return 0;

	(*s) = r;
	return 1;
}

void trysol(long long x, long long y)
{
	if (x < y || x < -32768 || x > 32767 || y < -32768 || y > 32768)
		return;

	if (((x + y) * y) != p)
		return;

	if (((x - y) * x) != q)
		return;

	solx[nsol] = (int)x;
	soly[nsol] = (int)y;
	nsol++;
}

void sol_q0()
{
	long long t;

	if (q != 0 || p < 0)
		return;

	if (perfect(p, &t)) {
		trysol(0, -t);
		trysol(0, t);
	}

	if ((p % 2) == 0 && perfect(p / 2, &t)) {
		trysol(-t, -t);
		trysol(t, t);
	}
}

void tryx(long long x)
{
	if (x < -32768 || x > 32767)
		return;

	if (x == 0 || (q % x) != 0)
		return;

	trysol(x, x - (q / x));
	trysol(-x, -x + (q / x));
}

void sol_gen()
{
	long long d, t, x;

	if (q == 0)
		return;

	d = p * p + 6 * p * q + q * q;
	if (d < 0)
		return;

	if (!perfect(d, &d))
		return;

	t = p + 3 * q + d;
	if (t >= 0 && (t % 4) == 0 && perfect(t / 4, &x))
		tryx(x);

	t = p + 3 * q - d;
	if (t >= 0 && (t % 4) == 0 && perfect(t / 4, &x))
		tryx(x);
}

int main()
{
	int i, k, c, p0, q0, t;

	for (scanf("%d", &t), c = 1; c <= t && scanf("%d %d", &p0, &q0) == 2; c++) {
		p = p0;
		q = q0;

		printf("Case %d:\n", c);

		nsol = 0;

		if (q == 0)
			sol_q0();
		else
			sol_gen();

		if (nsol == 0) {
			printf("Impossible.\n");
			continue;
		}

		for (i = 1, k = 0; i < nsol; i++)
			if ((solx[i] < solx[k]) ||
			    (solx[i] == solx[k] && soly[i] < soly[k]))
				k = i;

		printf("%d %d\n", solx[k], soly[k]);
	}

	return 0;
}
