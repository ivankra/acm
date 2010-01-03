#include <stdio.h>
#include <string.h>

int main()
{
	static char buf[1048576], buf2[256];
	char *s;
	int i, k, d;
	long long r;

	while (scanf(" %s %s %d", buf, buf2, &d) == 3) {
		for (s = buf; *s && *s == '+'; s++);

		if (buf2[0] == '/') {
			for (k = 0, r = 0; *s;) {
				r = r * 10LL + *s++ - '0';
				i = r / (long long)d;
				r %= (long long)d;

				if (k != 0 || i != 0) {
					putchar(i + '0');
					k++;
				}
			}

			if (k == 0)
				putchar('0');

			putchar('\n');
		} else {
			for (r = 0; *s;)
				r = (r * 10LL + *s++ - '0') % (long long)d;
			printf("%lld\n", r);
		}
	}

	return 0;
}
