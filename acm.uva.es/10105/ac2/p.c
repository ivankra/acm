#include <stdio.h>

static unsigned f[16], isdig[256], isdigz[256];

static void mktab()
{
	register unsigned i;

	for (i = 0; i < 256; i++) isdig[i] = 0;
	for (i = '0'; i <= '9'; i++) isdig[i] = 1;

	for (i = 0; i < 256; i++) isdigz[i] = isdig[i];
	isdigz[0] = 1;

	for (f[0] = 1, i = 1; i <= 12; i++)
		f[i] = i * f[i - 1];
}

int main()
{
	static unsigned char inbuf[1048576];
	register unsigned char *inp;
	register unsigned k, a, r;

	mktab();

	inbuf[read(0, inp = inbuf, sizeof(inbuf))] = 0;

#define READ(var) { \
	while (!isdigz[*inp]) inp++; \
	if (*inp == 0) return 0; \
	for (var = *inp++ - '0'; isdig[*inp];) \
		var = var * 10 + *inp++ - '0'; \
}

	for (;;) {
		READ(k);
		r = f[k];

		READ(k);

		while (k-- > 0) {
			READ(a);
			r /= f[a];
		}

		printf("%d\n", r);
	}

	return 0;
}
