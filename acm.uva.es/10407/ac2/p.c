#include <stdio.h>

int read(int, char *, int);

static int gcd(int a, int b)
{
	register int k = 0;

	if (a != 0 && b != 0)
		while (((a | b) & 1) == 0) a >>= 1, b >>= 1, k++;

	for (;;) {
		if (a == 0) return b;
		if (b == 0) return a;

		while ((a & 1) == 0) a >>= 1;
		while ((b & 1) == 0) b >>= 1;

		if (a > b)
			a -= b;
		else
			b -= a;
	}
}

int main()
{
	static char inbuf[65536];
	static int isdig[256], isdigm[256], insign;
	static int n, m, a, b;
	register char *inptr;
	register int inleft, i;

	for (i = 0; i < 256; i++)
		isdigm[i] = isdig[i] = (i >= '0' && i <= '9');
	isdigm['-'] = 1;

#define READ(var, eofcode)\
{\
	for (;;) {\
		if (inleft == 0) {\
			inleft = read(0, inptr = inbuf, sizeof(inbuf));\
			if (inleft <= 0) { eofcode; break; }\
		}\
		if (isdigm[(unsigned)*inptr]) break; else {inptr++; inleft--;}\
	}\
	if (*inptr == '-') { var = 0; inptr++; inleft--; insign = -1; } \
	  else { var = *inptr++ - '0'; inleft--; insign = 1; } \
	for (;;) {\
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
	var *= insign; \
}

	inptr = inbuf;
	inleft = 0;

	for (n = 0, m = 0;;) {
		READ(a, { return 0; });

		if (a == 0) {
			if (n == 0) break;
			printf("%d\n", m);
			n = 0;
		} else if (n == 0) {
			n = 1;
			m = a;
			b = a;
		} else {
			if (n++ == 1)
				m = (a > b) ? (a - b) : (b - a);
			else
				m = gcd(m, (a > b) ? (a - b) : (b - a));
			b = a;
		}
	}

fflush(stdout);
_exit(0);
	return 0;
}
