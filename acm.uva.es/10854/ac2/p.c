#include <stdio.h>
#include <string.h>

extern int read(int, char *, int);

static char inbuf[1048576], *inptr;
static int isdig[256], isword[256];

#define NEXT { while(isword[*inptr]) inptr++; while(!isword[*inptr]) inptr++; }

static long long solve(void)
{
	long long r, s;

	for (r = 1;;) {
		if (*inptr == 'I') {
			NEXT;
			s = solve();
			NEXT;
			r *= (s + solve());
			NEXT;
		} else if (*inptr == 'S') {
			NEXT;
		} else {
			return r;
		}
	}
}

int main()
{
	int t;

	for (t = '0'; t <= '9'; t++) isdig[t] = 1;
	for (t = 'A'; t <= 'Z'; t++) isword[t] = 1;
	isword['_'] = 1;

	read(0, inptr = inbuf, sizeof(inbuf));

	while (!isdig[*inptr]) inptr++;
	for (t = 0; isdig[*inptr];)
		t = t * 10 + *inptr++ - '0';

	while (t-- > 0) {
		NEXT;
		printf("%lld\n", solve());
	}

	return 0;
}
