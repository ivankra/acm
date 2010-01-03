#include <stdio.h>

int write(int, char *, int);

int main()
{
	static char op[16], buf[65536];
	static int t, a, b;
	register char *p;
	register int i;

	scanf("%d", &t);

	for (p = buf; t-- > 0 && scanf(" %X %1[+-] %X", &a, op, &b) == 3;) {
		for (i = 12; i >= 0; i--)
			*p++ = ((a >> i) & 1) + '0';

		*p++ = ' ';
		*p++ = op[0];
		*p++ = ' ';

		for (i = 12; i >= 0; i--)
			*p++ = ((b >> i) & 1) + '0';

		*p++ = ' ';
		*p++ = '=';
		*p++ = ' ';

		if (op[0] == '+')
			a += b;
		else
			a -= b;

		if (a < 10) {
			*p++ = a + '0';
		} else if (a < 100) {
			*p++ = (a / 10) + '0';
			*p++ = (a % 10) + '0';
		} else if (a < 1000) {
			*p++ = (a / 100) + '0';
			*p++ = ((a / 10) % 10) + '0';
			*p++ = (a % 10) + '0';
		} else {
			*p++ = (a / 1000) + '0';
			*p++ = ((a / 100) % 10) + '0';
			*p++ = ((a / 10) % 10) + '0';
			*p++ = (a % 10) + '0';
		}

		*p++ = '\n';

		if ((p + 1024) > &buf[sizeof(buf)]) {
			write(1, buf, p - buf);
			p = buf;
		}
	}

	if (p != buf)
		write(1, buf, p - buf);

	return 0;
}
