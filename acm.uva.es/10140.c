#include <stdio.h>
#include <string.h>

#define MARK(x) bitmap[(x) >> 5] |= (1 << ((x) & 31))
#define GET(x) ((bitmap[(x) >> 5] >> ((x) & 31)) & 1)

unsigned primes[65536], sieve[65536], isprime[65536], low, up, diff;
unsigned bitmap[1048576];

static void check()
{
	register unsigned j, p, i;

	memset(bitmap, 0, ((up - low) >> 3) + 16);

	diff = up - low + 1;

	for (i = 0;;) {
		p = primes[i++];
		if ((p * p) > up) break;

		j = ((low + p - 1) / p);
		j = j * p - low;

		for (; j <= diff; j += p)
			MARK(j);
	}
}

static void mksieve()
{
	int i, j;

	memset(sieve, 0, sizeof(sieve));

	sieve[0] = sieve[1] = 1;
	for (i = 2; i < 256; i++)
		if (sieve[i] == 0)
			for (j = i * i; j < 65536; j += i) sieve[j] = 1;

	for (j = 0, i = 2; i < 65536; i++)
		if (sieve[i] == 0) primes[j++] = i;
}


int main()
{
	int p1, d1, p2, d2, q, d, i, j;

	mksieve();

	while (scanf("%u %u", &low, &up) == 2) {
		check();

		p1 = p2 = d2 = q = -1;
		d1 = 0x7FFFFFFF;

		for (i = low, j = 0; i <= up; i++, j++) {
			if (i < 65536) {
				if (sieve[i]) continue;
			} else if (GET(j)) {
				continue;
			}

			if (q >= 0) {
				d = i - q;

				if (d < d1)
					p1 = q, d1 = d;

				if (d > d2)
					p2 = q, d2 = d;
			}

			q = i;
		}

		if (p1 < 0)
			printf("There are no adjacent primes.\n");
		else
			printf("%d,%d are closest, %d,%d are most distant.\n",
				p1, p1 + d1, p2, p2 + d2);
	}

	return 0;
}
