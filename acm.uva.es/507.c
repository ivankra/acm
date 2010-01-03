#include <stdio.h>

int read(int, char *, int);

int main()
{
	static int isdig[256], isdigx[256], b, t;
	static int best, best_end, best_len;
	static char inbuf[8*1048576];
	char *inptr;
	int i, j, k, n, s;

	for (i = 0; i < 256; i++)
		isdigx[i] = isdig[i] = (i >= '0' && i <= '9');
	isdigx[0] = 1;
	isdigx['-'] = 1;

	inbuf[read(0, inptr = inbuf, sizeof(inbuf))] = '\0';

#define READ(x) {\
	while (!isdigx[(int)*inptr]) inptr++;\
	if (*inptr == '\0') return 0;\
	else if (*inptr == '-') {\
		for (inptr++,x=0;isdig[(int)*inptr];) x=x*10+(*inptr++)-'0';\
		x = -x;\
	} else {\
		for (x=(*inptr++)-'0';isdig[(int)*inptr];)x=x*10+(*inptr++)-'0';\
	}\
}

	READ(b);
	for (t = 1; t <= b; t++) {
		best = -1;

		READ(n);
		for (i = 1, k = s = 0; i < n; i++) {
			READ(j);

			s += j;
			k++;

			if (s < 0) {
				s = 0;
				k = 0;
			} else if (s > best || (s == best && k > best_len)) {
				best = s;
				best_len = k;
				best_end = i;
			}
		}

		if (best <= 0) {
			printf("Route %d has no nice parts\n", t);
		} else {
			printf("The nicest part of route %d is between stops %d and %d\n",
				t, best_end - best_len + 1, best_end + 1);
		}
	}

	return 0;
}
