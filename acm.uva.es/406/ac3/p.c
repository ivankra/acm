#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

#define MAXN 1020

static int sieve[MAXN], primes[MAXN], pi[MAXN], n, c, k;
static char numbers[MAXN][8], buffer[65536], *bufptr, *inptr;
static char input[2*65536];

#define PUTC(c) *bufptr++ = (c);
#define PUTS(s) { register char *p = (s); while (*p) *bufptr++ = *p++; }

int read(int, char *, int);
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

	for (i = 0; (j = read(0, input + i, sizeof(input) - i)) > 0;)
		i += j;
	input[i] = '\0';

	for (bufptr = buffer, inptr = input;;) {
		while (*inptr && (*inptr < '0' || *inptr > '9')) inptr++;
		if (*inptr == '\0') break;

		while (*inptr == '0') inptr++;
		for (n = 0; *inptr >= '0' && *inptr <= '9';)
			n = n * 10 + (*inptr++) - '0';

		while (*inptr && (*inptr < '0' || *inptr > '9')) inptr++;
		while (*inptr == '0') inptr++;
		for (c = 0; *inptr >= '0' && *inptr <= '9';)
			c = c * 10 + (*inptr++) - '0';

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
