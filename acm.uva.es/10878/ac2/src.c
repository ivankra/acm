#include <stdio.h>

int main2()
{
	static char inbuf[1048576], outbuf[1048576];
	char *p, *q;
	int b;

	inbuf[read(0, p = inbuf, sizeof(inbuf))] = '\0';
	q = outbuf;

	for (;;) {
		while (*p && *p != '|') p++;
		if (*p++ != '|') break;

		for (b = 0; *p != '|'; p++)
			if (*p == ' ')
				b <<= 1;
			else if (*p == 'o')
				b = (b << 1) | 1;
		p++;

		*q++ = b & 0xff;
	}

	write(1, outbuf, q - outbuf);
	exit(0);
	return 0;
}
