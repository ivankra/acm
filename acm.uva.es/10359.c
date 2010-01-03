#include <stdio.h>
#include <memory.h>

#define MAXDIG 80

static char tab[256][MAXDIG], buf[MAXDIG+16];
static int n;

int write(int, char *, int);

int main()
{
	register int i, j, c;
	register char *p, *q;

	memset(tab[0], 0, MAXDIG);
	tab[0][0] = 1;

	memset(tab[1], 0, MAXDIG);
	tab[1][0] = 1;

	for (i = 2; i < 256; i++) {
		memcpy(tab[i], tab[i-1], MAXDIG);
		for (j = 0, c = 0, p = tab[i], q = tab[i-2]; j < MAXDIG; j++) {
			c += *p + (*q++ << 1);
			if (c < 10) {
				*p++ = c;
				c = 0;
			} else if (c < 20) {
				*p++ = c - 10;
				c = 1;
			} else {
				*p++ = c - 20;
				c = 2;
			}
		}
	}

	while (scanf("%d", &n) == 1) {
		for (i = MAXDIG - 1, p = tab[n]; i > 0 && p[i] == 0; i--);

		for (j = 0; i >= 0; i--)
			buf[j++] = '0' + p[i];
		buf[j++] = '\n';

		write(1, buf, j);
	}

	return 0;
}
