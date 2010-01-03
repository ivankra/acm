#include <stdio.h>
#include <ctype.h>

int main()
{
	static char buf[16384], s[16384];
	static int a, b, i, d;
	static long long x;
	char *p, *q;

	while (gets(buf)) {
		for (p = buf; *p && (*p < '0' || *p > '9'); p++);
		if (*p == '\0') continue;

		for (a = 0; *p >= '0' && *p <= '9'; p++)
			a = a * 10 + *p - '0';

		while (*p && (*p < '0' || *p > '9'))
			p++;

		for (b = 0; *p >= '0' && *p <= '9'; p++)
			b = b * 10 + *p - '0';

		while (*p && !isalnum(*p)) p++;

		for (q = s; *p && isalnum(*p);)
			*q++ = *p++;
		*q = '\0';

		for (i = 0, x = 0, p = s; *p; p++) {
			if (*p >= '0' && *p <= '9')
				d = *p - '0';
			else if (*p >= 'A' && *p <= 'Z')
				d = *p - 'A' + 10;
			else if (*p >= 'a' && *p <= 'z')
				d = *p - 'a' + 10;

			if (d >= a) {
				x = -1;
				break;
			}

			x = x * (long long)a + (long long)d;
		}

		if (x < 0) {
			printf("%s is an illegal base %d number\n", s, a);
			continue;
		}

		for (i = 0; i == 0 || x > 0; i++, x /= b)
			buf[i] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"[x % b];

		printf("%s base %d = ", s, a);
		while (i-- > 0)
			putchar(buf[i]);
		printf(" base %d\n", b);
	}

	return 0;
}
