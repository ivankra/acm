#include <stdio.h>

int main()
{
	static char buf[16384];
	register unsigned long i, r;

	while (gets(buf) && buf[0] != '#') {
		for (r = 0, i = 0; buf[i]; i++)
			r = ((r << 8) + (unsigned)buf[i]) % 34943;

		r = (34943 - ((r << 16) % 34943)) % 34943;

		printf("%.2X %.2X\n", r >> 8, r & 0xFF);
	}

	return 0;
}
