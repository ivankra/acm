#include <stdio.h>
#include <string.h>
#include <math.h>

#define PI 63

#define MAXDIG 1024
#define RADIX 10

static int primes[PI] = {
	2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67,
	71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139,
	149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199, 211, 223,
	227, 229, 233, 239, 241, 251, 257, 263, 269, 271, 277, 281, 283, 293,
	307
};

static int ffact[512][PI];

static void tetra(int out[MAXDIG], int a[4], int p[4])
{
	static int e[PI];
	register int i, j, k, c, n;

	for (i = 0, k = 0; i < 4; i++)
		k += p[i];

	for (i = 0; i < PI; i++) {
		for (e[i] = ffact[k][i], j = 0; j < 4; j++)
			e[i] -= ffact[p[j]][i];
	}

	for (i = 0; i < 4; i++) {
		for (k = a[i], j = 0; k > 1; j++) {
			while ((k % primes[j]) == 0) {
				k /= primes[j];
				e[j] += p[i];
			}
		}
	}

	for (out[0] = 1, n = 1, i = 1; i < MAXDIG; i++)
		out[i] = 0;

	for (k = 0; k < PI; k++) {
		for (j = 0; j < e[k]; j++) {
			for (i = 0, c = 0; (i < n || c != 0); i++) {
				c += out[i] * primes[k];
				out[i] = (c % 10);
				c /= 10;
			}

			if (i > n)
				n = i;
		}
	}
}

static void mktab()
{
	int i, j, k;

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

static int compare(int x[], int y[])
{
	register int i;

	for (i = MAXDIG - 1; i >= 0; i--)
		if (x[i] != y[i]) return ((x[i] > y[i]) ? 1 : -1);

	return 0;
}

int main()
{
	static int n, c[4], r[4], rmin[4], rmax[4];
	static int maxnum[MAXDIG], num[MAXDIG];
	static char buf1[1024], buf2[1024];
	register int i, j, k;

	mktab();

	while (scanf("%d %d %d %d %d", &n, &c[0], &c[1], &c[2], &c[3]) == 5) {
		if (n == 0)
			break;

		for (i = 0, j = 0; i < 4; i++)
			j += c[i];

		for (i = 0; i < 4; i++) {
			r[i] = (c[i] * n + (j >> 1)) / j;

			rmin[i] = r[i] - 1;
			if (rmin[i] < 0) rmin[i] = 0;

			rmax[i] = r[i] + 1;
			if (rmax[i] > n) rmax[i] = n;

			r[i] = rmin[i];
		}

		memset(maxnum, 0, sizeof(maxnum));

		for (;;) {
			for (i = 0, j = 0; i < 4; i++)
				j += r[i];

			if (j == n) {
				tetra(num, c, r);
				if (compare(num, maxnum) > 0)
					memcpy(maxnum, num, sizeof(num));
			}

			for (i = 0; i < 4 && ++r[i] > rmax[i]; i++)
				r[i] = rmin[i];

			if (i == 4)
				break;
		}

		for (i = 0; maxnum[i] == 0; i++);
		for (k = MAXDIG - 1; maxnum[k] == 0; k--);

		for (j = 0; j < 8 && i <= k; i++)
			buf1[j++] = maxnum[i] + '0';

		for (i = 0; j-- > 0;)
			buf2[i++] = buf1[j];
		buf2[i] = '\0';

		printf("%s\n", buf2);
	}

	return 0;
}
