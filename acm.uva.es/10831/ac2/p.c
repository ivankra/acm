#include <stdio.h>

int read(int, char *, int);

static int modexp(int b, int e, int m)
{
	int r;

	for (r = 1; e > 0; e >>= 1) {
		if (e & 1)
			r = (int)(((long long)r * (long long)b) % (long long)m);

		b = (int)(((long long)b * (long long)b) % (long long)m);
	}

	return r;
}


int main()
{
	static char inbuf[65536], outbuf[4*65536];
	static int isdig[256], isdigm[256], a, p;
	register char *inptr;
	register int f;

	for (f = 0; f < 256; f++) isdig[f] = 0;
	for (f = '0'; f <= '9'; f++) isdig[f] = 1;

	for (f = 0; f < 256; f++) isdigm[f] = isdig[f];
	isdigm['-'] = 1;

#define READ(var, eofcode)\
{\
	for (;;) {\
		if (f == 0) {\
			f = read(0, inptr = inbuf, sizeof(inbuf));\
			if (f <= 0) { eofcode; break; }\
		}\
		if (isdigm[(unsigned)*inptr]) break; else {inptr++; f--;}\
	}\
	if (*inptr == '-') { eofcode; } \
	for (var = *inptr++ - '0', f--;;) {\
		if (f == 0) {\
			f = read(0, inptr = inbuf, sizeof(inbuf));\
			if (f <= 0) { break; }\
		}\
		if (isdig[(unsigned)*inptr]) {\
			var = var * 10 + *inptr++ - '0';\
			f--;\
		} else {\
			break;\
		}\
	}\
}

	inptr = inbuf;
	f = 0;

	for (;;) {
		READ(a, { return 0; });
		READ(p, { return 0; });

		a %= p;

		if (a <= 1 || p <= 2 || modexp(a, (p - 1) / 2, p) == 1)
			printf("Yes\n");
		else
			printf("No\n");
	}

	return 0;
}
