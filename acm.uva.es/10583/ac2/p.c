#include <stdio.h>

int read(int, unsigned char *, unsigned);

static unsigned isdig[256], isdigz[256];

static void mktab()
{
	register unsigned i;

	for (i = 0; i < 256; i++) isdig[i] = 0;
	for (i = '0'; i <= '9'; i++) isdig[i] = 1;

	for (i = 0; i < 256; i++) isdigz[i] = isdig[i];
	isdigz[0] = 1;
}

int main()
{
	static unsigned char inbuf[6*1048576];
	static int x, y, n, m, r, t, p[65536];
	register int i;
	register unsigned char *inp;

	mktab();

	inbuf[read(0, inp = inbuf, sizeof(inbuf))] = 0;

#define READ(var) { \
	while (!isdigz[*inp]) inp++; \
	if (*inp == 0) return 0; \
	for (var = *inp++ - '0'; isdig[*inp];) \
		var = var * 10 + *inp++ - '0'; \
}

	for (t = 1;; t++) {
		READ(n);
		READ(m);

		if (n == 0)
			break;

		for (r = n, i = 1; i <= n; i++)
			p[i] = i;

		while (m-- > 0) {
			READ(x);
			READ(y);

			for (i = x; p[i] != i; i = p[i]);
			p[x] = i;

			for (i = y; p[i] != i; i = p[i]);
			p[y] = i;

			if (p[x] == p[y])
				continue;

			p[p[x]] = i;
			r--;
		}

		printf("Case %d: %d\n", t, r);
	}

	return 0;
}
