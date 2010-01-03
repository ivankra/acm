#include <stdio.h>

#define PI 25

static int primes[PI] = {
	2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61,
	67, 71, 73, 79, 83, 89, 97
};

int main()
{
	static int ffact[101][PI], p[PI], n, d;
	static long long r;
	register int i, j, k;

	for (i = 0; i < PI; i++)
		ffact[0][i] = ffact[1][i] = 0;

	for (i = 1; i <= 100; i++) {
		for (j = 0; j < PI; j++)
			ffact[i][j] = ffact[i - 1][j];

		for (k = i, j = 0; j < PI && k > 1; j++)
			for (; (k % primes[j]) == 0; k /= primes[j])
				ffact[i][j]++;
	}

	while (scanf("%d %d", &n, &d) == 2 && (n | d) != 0) {
		if (d < 0)
			d = -d;

		for (i = 0; i < PI && d > 1; i++)
			for (p[i] = 0; (d % primes[i]) == 0; d /= primes[i])
				p[i]++;

		if (d != 1) {
			printf("0\n");
			continue;
		}

		for (; i < PI; i++)
			p[i] = 0;

		for (r = 1, i = 0; i < PI; i++) {
			if (p[i] > ffact[n][i]) {
				r = 0;
				break;
			} else {
				r *= (long long)(ffact[n][i] - p[i] + 1);
			}
		}

		printf("%lld\n", r);
	}

	return 0;
}
