#include <stdio.h>
#include <string.h>

int main()
{
	static char r[128], buf[128];
	register int i, j, c;

	memset(r, 0, sizeof(r));

	while (scanf(" %127[0-9]", buf) == 1 && strcmp(buf, "0") != 0) {
		for (i = 0; buf[i]; i++);

		for (i--, j = 0, c = 0; i >= 0; i--) {
			if (buf[i] < '0' || buf[i] > '9')
				continue;

			c += r[j] + (buf[i] - '0');

			if (c < 10) {
				r[j++] = c;
				c = 0;
			} else {
				r[j++] = c - 10;
				c = 1;
			}
		}

		if (c != 0) {
			for (; j < 128; j++) {
				if (r[j] < 9) {
					r[j]++;
					break;
				} else {
					r[j] = 0;
				}
			}
		}
	}

	for (i = 127; i > 0 && r[i] == 0; i--);

	while (i >= 0)
		putchar(r[i--] + '0');
	putchar('\n');

	return 0;
}
