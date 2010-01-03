#include <stdio.h>

int read(int, char *, int);
int write(int, const char *, int);

int main()
{
	static int parent[32768], count[32768];
	static int isdig[256], r, t, a, b, n, m;
	static char inbuf[16384];
	register int i, inleft;
	register char *inptr;

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
			if (inleft <= 0) break;\
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

	READ(t, { return 0; });

	while (t-- > 0) {
		READ(n, { return 0; });
		READ(m, { return 0; });

		for (i = 1; i <= n; i++)
			parent[i] = i;

		for (i = 1; i <= n; i++)
			count[i] = 1;

		for (r = 1; m-- > 0;) {
			READ(a, { return 0; });
			READ(b, { return 0; });

			if (a == b)
				continue;

			for (i = a; parent[i] != i; i = parent[i]);
			a = (parent[a] = i);

			for (i = b; parent[i] != i; i = parent[i]);
			b = (parent[b] = i);

			if (a == b)
				continue;

			if (count[a] >= count[b]) {
				parent[b] = a;
				if ((count[a] += count[b]) > r)
					r = count[a];
			} else {
				parent[a] = b;
				if ((count[b] += count[a]) > r)
					r = count[b];
			}
		}

		printf("%d\n", r);
	}

	return 0;
}
