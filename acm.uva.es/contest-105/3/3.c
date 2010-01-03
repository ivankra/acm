/*
    S^S / ((S-1) ^ S) * x
    x = Sk
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define NPRIMES 25

int primes[NPRIMES] = {
	2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97
};

void factor(int n, int *f)
{
	register int i, j, p;

	for (i = 0; i < NPRIMES; i++)
		f[i] = 0;

	for (;;) {
		for (i = 0;; i++)
			if (i >= NPRIMES || n < primes[i])
				return;
			else if ((n % primes[i]) == 0)
				break;

		for (j = 0, p = primes[i]; n >= p && (n % p) == 0; n /= p, j++);

		f[i] += j;
	}
}

int main()
{
	int fn[NPRIMES], fd[NPRIMES], fc[NPRIMES];
	int i, s;
	double c;

	for (s = 2; s <= 100; s++) {
		factor(s, fn);
		factor(s-1, fd);

		for (i = 0; i < s; i++) {
			fn[i] *= (s + 1);
			fd[i] *= s;
		}

		/* calculate complement to denominator */
		for (i = 0; i < NPRIMES; i++) {
			if (fn[i] >= fd[i])
				fc[i] = 0;
			else
				fc[i] = fd[i] - fn[i];
		}

		for (c = 1, i = 0; i < NPRIMES; i++)
			if (fc[i])
				c *= pow((double)primes[i], (double)fc[i]);

		printf("S=%3d complement: 1 ", s);
		for (i = 0; i < NPRIMES; i++)
			if (fc[i]) printf((fc[i] > 1) ? " %d^%d" : " %d", primes[i], fc[i]);

		if (c > (double)0x7FFFFFFF)
			printf(" [TOO LARGE]\n");
		else
			printf(" = %u\n", (unsigned long)c);
	}
	fflush(stdout);

}
