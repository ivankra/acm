#include <stdio.h>
#include <stdlib.h>

int read(int, char *, int);

typedef unsigned long long num;

static int p[256];

static int f(num x)
{
	int i, j, r;
	unsigned y;

	r = 1; i = 0;

if (x < 0xFFFFFFFFULL) goto sh;

	for (; (p[i] * p[i]) <= x;) {
		if ((x % p[i]) == 0) {
			for (x /= p[i], j = 2; (x % p[i]) == 0; j++, x /= p[i]);
			r *= j;
			i++;
			if (x < 0xFFFFFFFFULL) goto sh;
		} else {
			i++;
		}
	}

sh:	y = x;
	for (; (p[i] * p[i]) <= y; i++) {
		if ((y % p[i]) == 0) {
			for (y /= p[i], j = 2; (y % p[i]) == 0; j++, y /= p[i]);
			r *= j;
		}
	}

	return (y == 1) ? r : (r << 1);
}

void sieve()
{
	static char s[1024];
	int i, j;

	/*memset(s, 0, sizeof(s));*/

	for (i = 2; i < 32; i++)
		if (s[i] == 0) for (j = i * i; j < 1024; j += i) s[j] = 1;

	for (i = 2, j = 0; i < 1024; i++)
		if (s[i] == 0) p[j++] = i;
}

int main()
{
	static char inbuf[16384];
	static int d[128];
	char *p;
	int i, t;
	num x;

	sieve();

	for (i = '0'; i <= '9'; i++) d[i] = 1;
	read(0, p = inbuf, sizeof(inbuf));
#define R(z) {while(!d[*p])p++;for(z=(*p++)-'0';d[*p];)z=z*10+(*p++)-'0';p++;}

	for (t = 1;; t++) {
		R(i); if (i == 0) break;
		x = i;
		R(i); x *= i;
		R(i); i *= i; x *= i;

		printf("Case %d: %d\n", t, 2 * f(x) - 1);
	}

	exit(0);
}
