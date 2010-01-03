#include <stdio.h>
#include <stdlib.h>

int read(int, char *, int);
int write(int, char *, int);

int main2()
{
	static int isdig[256], sieve[4000], prime[4000];
	static char inbuf[1048576], outbuf[1048576], tmp[256];
	char *p, *q, *s;
	int i, j, c, t, n, m;

	/*memset(sieve, 0, sizeof(sieve));*/
	for (i = 2; i < 58; i++)
		if (sieve[i] == 0)
			for (j = i * i; j < 3165; j += i) sieve[j] = 1;

	for (prime[0] = 2, j = 1, i = 3; i < 3165; i += 2)
		if (sieve[i] == 0) prime[j++] = i;

	/*memset(isdig, 0, sizeof(isdig));*/
	for (i = '0'; i <= '9'; i++) isdig[i] = 1;

	read(0, p = inbuf, sizeof(inbuf));
	q = outbuf;

#define R(x) {while(!isdig[*p])p++;for(x=*p++-'0';isdig[*p];)x=x*10+*p++-'0';}
#define P(c) {*q++=(c);}
#define W(ex) {int x=(ex);for(s=tmp;x>0;x/=10)*s++=(x%10)+'0';while(s-->tmp)*q++=*s;}

	R(t);
	for (c = 1; c <= t; c++) {
		R(n);
		P('C');P('a');P('s');P('e');P(' ');P('#');W(c);P(':');P(' ');

		if ((n & 3) == 0) {
			W(n);P(' ');P('=');P(' ');P('2');P(' ');P('*');P(' ');
			W(n>>1);P(' ');P('=');P(' ');P('4');P(' ');P('*');P(' ');
			W(n>>2);P('\n');
		} else if ((n & 1) == 0) {
			m = n >> 1;
			for (j = 1; (m % prime[j]) != 0; j++);
			W(n);P(' ');P('=');P(' ');P('2');P(' ');P('*');P(' ');
			W(m);P(' ');P('=');P(' ');W(prime[j]<<1);P(' ');P('*');
			P(' ');W(m/prime[j]);P('\n');
		} else {
			for (i = 1; (n % prime[i]) != 0; i++);
			m = n / prime[i];
			for (j = i; (m % prime[j]) != 0; j++);

			W(n);P(' ');P('=');P(' ');W(prime[i]);P(' ');P('*');
			P(' ');W(m);P(' ');P('=');P(' ');W(prime[i]*prime[j]);
			P(' ');P('*');P(' ');W(m/prime[j]);P('\n');
		}
	}

	write(1, outbuf, q - outbuf);
	exit(0);
	return 0;
}
