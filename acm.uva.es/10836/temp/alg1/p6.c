#include <stdio.h>
#include <string.h>
#include <math.h>

#define PI 63

typedef unsigned long long u_int64_t;

static int primes[PI] = {
	2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67,
	71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139,
	149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199, 211, 223,
	227, 229, 233, 239, 241, 251, 257, 263, 269, 271, 277, 281, 283, 293,
	307
};

static double logf[512], logc[4];
static int ffact[512][PI], c[4], r[4], n;

static u_int64_t eval(int *overfl)
{
	static int e[PI];
	u_int64_t m;
	int i, j, k;

	for (i = 0; i < PI; i++) {
		for (e[i] = ffact[n][i], j = 0; j < 4; j++)
			e[i] -= ffact[r[j]][i];
	}

	for (i = 0; i < 4; i++) {
		for (k = c[i], j = 0; k > 1; j++) {
			while ((k % primes[j]) == 0) {
				k /= primes[j];
				e[j] += r[i];
			}
		}
	}

	i = (e[0] < e[2]) ? e[0] : e[2];
	e[0] -= i;
	e[2] -= i;

	(*overfl) = 0;

	for (i = 0, m = 1; i < PI; i++) {
		for (j = 0; j < e[i]; j++) {
			m = (m * (u_int64_t)primes[i]);
			if (m >=     100000000ULL) {
				(*overfl) = 1;
				m %= 100000000ULL;
			}
		}
	}

	return m;
}

static void mktab()
{
	int i, j, k;

	for (logf[0] = 0., i = 1; i < 350; i++)
		logf[i] = logf[i - 1] + log((double)i);

	memset(ffact, 0, sizeof(ffact));

	for (i = 1; i <= 305; i++) {
		for (j = 0; j < PI; j++)
			ffact[i][j] = ffact[i - 1][j];

		for (j = 0, k = i; k > 1; j++) {
			while ((k % primes[j]) == 0) {
				k /= primes[j];
				ffact[i][j]++;
			}
		}
	}
}

static void look()
{
	static int g[4], a[4], rmin[4], rmax[4];
	static double rlog;
	register int i, j;
	double u;

	for (i = 0, j = 0; i < 4; i++)
		j += c[i];

	for (i = 0; i < 4; i++) {
		g[i] = (c[i] * n + (j >> 1)) / j;

		rmin[i] = g[i] - 8;
		if (rmin[i] < 0) rmin[i] = 0;

		rmax[i] = g[i] + 8;
		if (rmax[i] > n) rmax[i] = n;

		r[i] = a[i] = rmin[i];
	}

	for (rlog = -999999;;) {
		for (i = 0, j = 0; i < 4; i++)
			j += a[i];

		if (j == n) {
			for (u = logf[n], i = 0; i < 4; i++)
				u += (double)a[i] * logc[i] - logf[a[i]];

			if (u > rlog)
				for (rlog = u, i = 0; i < 4; i++) r[i] = a[i];
		}

		for (i = 0; i < 4 && ++a[i] > rmax[i]; i++)
			a[i] = rmin[i];

		if (i == 4)
			break;
	}

if (rlog < 1.) { char *p; for(p=NULL;;) *p++=42; }

}

int main()
{
	int i, fl;
	u_int64_t a;

	mktab();

	while (scanf("%d %d %d %d %d", &n, &c[0], &c[1], &c[2], &c[3]) == 5) {
		if (n == 0)
			break;

		for (i = 0; i < 4; i++)
			logc[i] = log((double)c[i]);

		look();

		a = eval(&fl);
		if (fl)
			printf("%.8u\n", (unsigned)a);
		else
			printf("%u\n", (unsigned)a);
	}

	return 0;
}
