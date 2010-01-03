#include <stdio.h>

int read(int, char *, int);

static unsigned isdig[256], isdigz[256];

static void mktab()
{
	unsigned i;

	for (i = 0; i < 256; i++) isdig[i] = 0;
	for (i = '0'; i <= '9'; i++) isdig[i] = 1;

	for (i = 0; i < 256; i++) isdigz[i] = isdig[i];
	isdigz[0] = 1;
}

int main()
{
	static unsigned char inbuf[5*1048576];
	static unsigned t, n;
	register unsigned char *inp;
	register unsigned m, a, x, y;

	mktab();

	inbuf[read(0, inp = inbuf, sizeof(inbuf))] = 0;

#define READ(var) { \
	while (!isdigz[*inp]) inp++; \
	if (*inp == 0) return 0; \
	for (var = *inp++ - '0'; isdig[*inp];) \
		var = var * 10 + *inp++ - '0'; \
}

	READ(t);

	while (t-- > 0) {
		READ(m);
		READ(n);

		for (x = 0, y = 0; n-- > 0;) {
			READ(a);

			if ((a + a) <= m) {
				x = (a > x) ? a : x;
				y = ((m - a) > y) ? (m - a) : y;
			} else {
				x = ((m - a) > x) ? (m - a) : x;
				y = (a > y) ? a : y;
			}
		}

		printf("%u %u\n", x, y);
	}

	return 0;
}
