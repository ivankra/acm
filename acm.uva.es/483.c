#include <stdio.h>

int main()
{
	static char buf[65536];
	int n, c;

	for (n = 0;;) {
		c = getchar();

		if (c == EOF || c <= 32) {
			while (n > 0)
				putchar(buf[--n]);

			if (c == EOF)
				break;

			putchar(c);
		} else {
			buf[n++] = c;
		}
	}

	return 0;
}
