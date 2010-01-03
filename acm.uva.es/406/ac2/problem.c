#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

#define MAXN 1020

static int sieve[MAXN], primes[MAXN], pi[MAXN], n, c, k;
static char numbers[MAXN][8], buffer[65536], *bufptr;

#define PUTC(c) *bufptr++ = (c);
#define PUTS(s) { register char *p = (s); while (*p) *bufptr++ = *p++; }

int write(int, char *, int);

int main()
{
	register int i, j;

	memset(sieve, '\0', sizeof(sieve));
	primes[0] = 1;
	pi[0] = 0;
	pi[1] = 1;
	for (i = 2, k = 1; i < MAXN; i++) {
		if (sieve[i] != 0) {
			pi[i] = k;
		} else {
			for (primes[k++] = i, j = i; j < MAXN; j += i)
				sieve[j] = 1;
			pi[i] = k;
		}
	}

	memset(numbers, '\0', sizeof(numbers));
	for (i = 0; i < MAXN; i++)
		sprintf(numbers[i], " %d", i);

	for (bufptr = buffer; scanf("%d %d", &n, &c) == 2;) {
		if ((k = pi[n]) & 1) {
			i = (k >> 1) - c + 1;
			j = (c << 1) - 1;
		} else {
			i = (k >> 1) - c;
			j = c << 1;
		}

		if (i < 0) i = 0;

		PUTS(numbers[n] + 1);
		PUTS(numbers[c]);
		PUTC(':');
		while (i < k && j-- > 0)
			PUTS(numbers[primes[i++]]);
		PUTC('\n');
		PUTC('\n');

		if (((bufptr - buffer) + 1024) >= sizeof(buffer)) {
			write(1, buffer, bufptr - buffer);
			bufptr = buffer;
		}
	}

	if (bufptr != buffer)
		write(1, buffer, bufptr - buffer);

	return 0;
}
