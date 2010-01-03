#include <stdio.h>

int main()
{
	static char buf[1024];
	static int hextab[256];
	register char *p;
	register int r;

	for (r = 0; r < 256; r++) hextab[r] = -1;
	for (r = 0; r < 10; r++) hextab['0' + r] = r;
	for (r = 0; r < 6; r++) hextab['A' + r] = hextab['a' + r] = 10 + r;

	while (gets(buf)) {
		for (p = buf; *p && (*p < '0' || *p > '9') && *p != '-'; p++);

		if (*p == '-')
			break;

		if (*p == '0' && p[1] == 'x') {
			for (p += 2, r = 0; hextab[(unsigned)*p] >= 0; p++)
				r = (r << 4) + hextab[(unsigned)*p];
			printf("%d\n", r);
		} else {
			for (r = 0; *p >= '0' && *p <= '9'; p++)
				r = r * 10 + *p - '0';
			printf("0x%X\n", r);
		}
	}

	return 0;
}
