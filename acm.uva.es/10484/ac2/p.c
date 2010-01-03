#include <stdio.h>

#define PI 25

static int primes[PI] = {
	2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61,
	67, 71, 73, 79, 83, 89, 97
};

int main()
{
	static char inbuf[65536];
	static int ffact[101][PI], p[PI], isdig[256], n, d;
	static long long r;
	register int i, j;
	register char *inptr;
	register int inleft;

	for (i = 0; i < 256; i++)
		isdig[i] = (i >= '0' && i <= '9');

#define READ(var, eofcode)\
{\
	for (;;) {\
		if (inleft == 0) {\
			inleft = read(0, inptr = inbuf, sizeof(inbuf));\
			if (inleft <= 0) { eofcode; break; }\
		}\
		if (isdig[(unsigned)*inptr]) break; else {inptr++; inleft--;}\
	}\
	for (var = *inptr++ - '0', inleft--;;) {\
		if (inleft == 0) {\
			inleft = read(0, inptr = inbuf, sizeof(inbuf));\
			if (inleft <= 0) { break; }\
		}\
		if (isdig[(unsigned)*inptr]) {\
			var = var * 10 + *inptr++ - '0';\
			inleft--;\
		} else {\
			break;\
		}\
	}\
}

	inptr = inbuf;
	inleft = 0;

	for (i = 0; i < PI; i++)
		ffact[0][i] = ffact[1][i] = 0;

	for (i = 1; i <= 100; i++) {
		register int k;

		for (j = 0; j < PI; j++)
			ffact[i][j] = ffact[i - 1][j];

		for (k = i, j = 0; j < PI && k > 1; j++)
			for (; (k % primes[j]) == 0; k /= primes[j])
				ffact[i][j]++;
	}

	for (;;) {
		READ(n, { return 0; });
		READ(d, { return 0; });

		if ((n | d) == 0) break;

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
