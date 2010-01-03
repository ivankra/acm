#include <stdio.h>

int write(int, char *, int);

int main()
{
	static int c[9];
	static char buffer[65536], num[1200][8];
	register int i, k, s;
	register char *q;

	for (i = 0; i < 1100; i++)
		sprintf(num[i], "%d", i);

	q = buffer;

	while (scanf("%d %d %d %d %d %d %d %d %d", &c[8], &c[7], &c[6], &c[5],
		     &c[4], &c[3], &c[2], &c[1], &c[0]) == 9) {

		for (i = 8, s = 0; i > 0; i--) {
			if (c[i] == 0)
				continue;

			k = c[i];

			if (k < 0) {
				k = -k;
				if (s) {
					*q++ = ' '; *q++ = '-'; *q++ = ' ';
				} else {
					*q++ = '-';
				}
			} else if (s != 0) {
				*q++ = ' ';
				*q++ = '+';
				*q++ = ' ';
			}

			if (k != 1) {
				register char *p;
				for (p = num[k]; *p;)
					*q++ = *p++;
			}

			*q++ = 'x';

			if (i > 1) {
				*q++ = '^';
				*q++ = i + '0';
			}

			s = 1;
		}

		k = c[0];

		if (s && k != 0) {
			*q++ = ' ';
			if (k < 0) {
				k = -k;
				*q++ = '-';
			} else {
				*q++ = '+';
			}
			*q++ = ' ';
		} else if (s == 0 && k < 0) {
			*q++ = '-';
			k = -k;
		}

		if (s == 0 || k != 0) {
			register char *p;
			for (p = num[k]; *p;)
				*q++ = *p++;
		}

		*q++ = '\n';

		if ((q + 1024) > &buffer[sizeof(buffer)]) {
			write(1, buffer, q - buffer);
			q = buffer;
		}
	}

	if (q != buffer)
		write(1, buffer, q - buffer);

	return 0;
}
