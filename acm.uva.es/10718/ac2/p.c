#include <stdio.h>

int main()
{
	static char inbuf[65536];
	static int isdig[256];
	static unsigned n, u, m;
	register char *inptr;
	register int inleft, i, t;

	for (i = 0; i < 256; i++)
		isdig[i] = (i >= '0' && i <= '9');

#define READ(var, eofcode)\
{\
	for (;;) {\
		if (inleft == 0) {\
			inleft = read(0, inptr = inbuf, sizeof(inbuf));\
			if (inleft <= 0) { eofcode; break; }\
		}\
		if (isdig[(unsigned)*inptr]) break; else {inptr++; inleft--;}\
	}\
	for (var = *inptr++ - '0', inleft--;;) {\
		if (inleft == 0) {\
			inleft = read(0, inptr = inbuf, sizeof(inbuf));\
			if (inleft <= 0) { break; }\
		}\
		if (isdig[(unsigned)*inptr]) {\
			var = var * 10 + *inptr++ - '0';\
			inleft--;\
		} else {\
			break;\
		}\
	}\
}

	inptr = inbuf;
	inleft = 0;

	for (;;) {
		READ(n, { return 0; });
		READ(m, { return 0; });
		READ(u, { return 0; });

		for (i = 31; i >= 0; i--) {
			t = (1 << i);

			if ((m & t) == 0 && (n & t) == 0 &&
			    ((m | t) & ~((1 << i) - 1)) <= u) {
				m |= t;
				m &= ~((1 << i) - 1);
			}
		}

		printf("%u\n", m);
	}

	return 0;
}
