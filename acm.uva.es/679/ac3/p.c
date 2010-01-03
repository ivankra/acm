#include <stdio.h>

int read(int, char *, int);
int write(int, const char *, int);

int main()
{
	static char inbuf[16384], outbuf[16384+16], tmp[16];
	static int isdig[256], t, d, s;
	register char *inptr, *outp;
	register int inleft, i, k;

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
			if (inleft <= 0)  break;\
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
	outp = outbuf;

	READ(t, { return 0; });

	while (t-- > 0) {
		READ(d, { goto ex; });
		READ(s, { goto ex; });

		for (i = 1, s--; d-- > 1; s >>= 1)
			i = (i << 1) + (s & 1);

		for (k = 0; i > 0; i /= 10)
			tmp[k++] = (i % 10) + '0';

		while (k-- > 0)
			*outp++ = tmp[k];
		*outp++ = '\n';

		if ((outp - outbuf) >= (sizeof(outbuf) - 16)) {
			write(1, outbuf, outp - outbuf);
			outp = outbuf;
		}
	}
ex:

	if (outp != outbuf)
		write(1, outbuf, outp - outbuf);

	return 0;
}
