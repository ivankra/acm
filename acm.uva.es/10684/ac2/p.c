#include <stdio.h>

int main()
{
	static int a, n, r, s;
	static char inbuf[65536];
	static int isdig[256], isdigm[256], sign;
	register char *inptr;
	register int inleft;

	for (a = 0; a < 256; a++)
		isdigm[a] = isdig[a] = (a >= '0' && a <= '9');
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
	if (*inptr == '-') { sign = -1; inptr++; inleft--; var = 0; }\
	  else { sign = 1; var = *inptr++ - '0'; inleft--; } \
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
	var *= sign; \
}

	inptr = inbuf;
	inleft = 0;
	for (;;) {
		READ(n, { return 0; });
		if (n <= 0) break;

		for (r = -1, s = 0; n-- > 0;) {
			READ(a, { return 0; });
			s += a;
			if (s < 0)
				s = 0;
			else if (s > r)
				r = s;
		}

		if (r <= 0)
			printf("Losing streak.\n");
		else
			printf("The maximum winning streak is %d.\n", r);
	}

	return 0;
}
