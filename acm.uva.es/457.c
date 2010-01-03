#include <stdio.h>

int write(int, char *, int);

static int d[10], s1[40], s2[40], *s, *q, i, k, t;
static char buffer[262144], *bufptr;

int main()
{
	scanf("%d", &t);

	for (bufptr = buffer; t-- > 0;) {
		for (i = 0; i < 10; i++)
			if (scanf("%d", &d[i]) < 1) break;
		if (i < 10) break;

		for (s = s1, q = s2, i = 0; i < 40; i++)
			s[i] = 0;
		s[19] = 1;

		for (k = 0; k < 50; k++) {
			for (i = 0; i < 40; i++)
				*bufptr++ = (" .xW"[s[i]]);
			*bufptr++ = '\n';

			if ((bufptr + 1024) > &buffer[sizeof(buffer)]) {
				write(1, buffer, bufptr - buffer);
				bufptr = buffer;
			}

			q[0] = d[s[0] + s[1]];
			for (i = 1; i < 39; i++)
				q[i] = d[s[i-1] + s[i] + s[i+1]];
			q[39] = d[s[38] + s[39]];

			s = q;
			q = (q == s1) ? s2 : s1;
		}

		if (t != 0)
			*bufptr++ = '\n';
	}

	if (buffer != bufptr)
		write(1, buffer, bufptr - buffer);

	return 0;
}
