#include <stdio.h>

int main()
{
	static int n, d, q[2048];
	static char buf[2048];
	register int k, i;
	char *p;

	while (scanf("%d%d", &n, &d) == 2 && d != 0) {
		for (k = 0; k < 1024; k++) q[k] = 0;

		p = buf;
		*p++ = '.';

		for (k = 1, i = 0; n > 0 && q[n] == 0; k++) {
			q[n] = k;

			if (++i >= 50) {
				*p++ = '\n';
				i = 0;
			}

			n *= 10;
			*p++ = (n / d) + '0';
			n %= d;
		}
		*p = '\0';

		if (n == 0)
			printf("%s\nThis expansion terminates.\n\n", buf);
		else
			printf("%s\nThe last %d digits repeat forever.\n\n",
			       buf, k - q[n]);
	}

	return 0;
}
