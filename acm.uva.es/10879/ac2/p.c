#include <stdio.h>
#include <stdlib.h>

int read(int, char *, int);

int main()
{
	static int isdig[256], sieve[4000], prime[4000];
	static char buf[1048576];
	char *p;
	int i, j, c, t, n, m;

	/*memset(sieve, 0, sizeof(sieve));*/
	for (i = 2; i < 58; i++)
		if (sieve[i] == 0)
			for (j = i * i; j < 3165; j += i) sieve[j] = 1;

	for (prime[0] = 2, j = 1, i = 3; i < 3165; i += 2)
		if (sieve[i] == 0) prime[j++] = i;

	/*memset(isdig, 0, sizeof(isdig));*/
	for (i = '0'; i <= '9'; i++) isdig[i] = 1;

	read(0, p = buf, sizeof(buf));

#define R(x) {while(!isdig[*p])p++;for(x=*p++-'0';isdig[*p];)x=x*10+*p++-'0';}

	R(t);
	for (c = 1; c <= t; c++) {
		R(n);
		if ((n & 3) == 0) {
			printf("Case #%d: %d = %d * %d = %d * %d\n",
				c, n, 2, n >> 1, 4, n >> 2);
		} else if ((n & 1) == 0) {
			m = n >> 1;
			for (j = 1; (m % prime[j]) != 0; j++);
			printf("Case #%d: %d = 2 * %d = %d * %d\n",
				c, n, m, prime[j] << 1, m / prime[j]);
		} else {
			for (i = 1; (n % prime[i]) != 0; i++);
			m = n / prime[i];
			for (j = i; (m % prime[j]) != 0; j++);
			printf("Case #%d: %d = %d * %d = %d * %d\n",
				c, n, prime[i], m, prime[i] * prime[j], m / prime[j]);
		}
	}

	exit(0);
	return 0;
}
